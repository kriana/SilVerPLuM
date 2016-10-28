#include "modmanager.h"
#include "profile.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include "globalsettings.h"
#include <quazip.h>
#include <JlCompress.h>
#include <random>
#include "utils.h"

const QStringList ModManager::FORBIDDEN_MOD_IDS = QStringList() << "stardewvalley" << "stardewvalley-savegames" << "stardewvalley-userdata" << "stardewvalley-content";

ModManager::ModManager(Profile *profile) : m_profile(profile)
{
    m_config = new QSettings(profile->profileBaseDir().absoluteFilePath("mod-config.ini"), QSettings::IniFormat);

    m_modRepository = new ModRepository(this);
    m_dependencyTree = new DependencyTree(this);
}

ModManager::~ModManager()
{
    delete m_modRepository;

    for(Modification * mod : m_mods)
    {
        delete mod;
    }

    delete m_config;    
}

Profile *ModManager::profile() const
{
    return m_profile;
}

void ModManager::initialize()
{
    reloadMods();
}

QList<Modification *> ModManager::getModifications()
{
    return QList<Modification*>(m_mods);
}

QList<Modification *> ModManager::getPartiallyActiveMods()
{
    QList<Modification*> result;

    for(Modification * mod : m_mods)
    {
        if(mod->isPartiallyEnabled())
        {
            result << mod;
        }
    }

    return result;
}

QList<Modification *> ModManager::getModsInPriorityOrder(QList<Modification *> unordered)
{
    std::sort(unordered.begin(), unordered.end(), [&](Modification * a, Modification * b) {

        int sa = getSortPriority(a->id());
        int sb = getSortPriority(b->id());

        return sa < sb;
    });

    return unordered;
}

Modification *ModManager::getModification(const QString &id)
{
    for(Modification * mod : m_mods)
    {
        if(mod->id() == id)
            return mod;
    }

    return nullptr;
}

bool ModManager::setEnabled(Pipeline *pip, bool enabled, bool prime)
{
    // If not supported by platform, skip mod
    if(enabled && pip->unsupported() && !GlobalSettings::instance()->getForceUnsupported())
        return -1;

    m_config->setValue(pip->mod()->id() + "/content/" + pip->id(), enabled);

    bool success = true;

    if(enabled && prime)
    {
        success &= pip->primePipeline(false);
    }

    emit updatedModStatus(pip->mod()->id(), pip->id(), enabled);

    return success;
}

bool ModManager::isEnabled(Pipeline *pip)
{
    if(!GlobalSettings::instance()->getForceUnsupported() && pip->unsupported())
        return false;

    return m_config->value(pip->mod()->id() + "/content/" + pip->id(), false).toBool();
}

int ModManager::getSortPriority(const QString &mod)
{
    Modification * m = getModification(mod);
    return m_config->value(mod + "/priority", m_mods.indexOf(m)).toInt();
}

void ModManager::writePriorities()
{
    for(int i = 0; i < m_mods.size(); ++i)
    {
        Modification * m = m_mods[i];
        m_config->setValue(m->id() + "/priority", i);
    }

    m_config->sync();
}

bool ModManager::priotizeUp(Modification *mod)
{
    int index = m_mods.indexOf(mod);

    if(index > 0)
    {
        Modification * t = m_mods[index - 1];
        m_mods[index - 1] = m_mods[index];
        m_mods[index] = t;

        writePriorities();

        emit updatedModList();
        return true;
    }

    return false;
}

bool ModManager::priotizeDown(Modification *mod)
{
    int index = m_mods.indexOf(mod);

    if(index < m_mods.size() - 1)
    {
        Modification * t = m_mods[index + 1];
        m_mods[index + 1] = m_mods[index];
        m_mods[index] = t;

        writePriorities();

        emit updatedModList();
        return true;
    }

    return false;
}

DependencyTree *ModManager::getDependencyTree() const
{
    return m_dependencyTree;
}

ModRepository *ModManager::getModRepository() const
{
    return m_modRepository;
}

QStringList ModManager::getUnloadableModPaths() const
{
    return m_unloadableModPaths;
}

QProcessEnvironment ModManager::processEnvironment()
{
    QProcessEnvironment env = profile()->processEnvironment();

    for(Modification * m : getModifications())
    {
        env.insert("SILVERPLUM_MOD_" + m->id().toUpper() + "_DIR", m->modBasePath().absolutePath());
    }

    return env;
}

Logger &ModManager::getLogger()
{
    return m_profile->getLogger();
}

bool ModManager::importModFromDirectory(const QDir &dir, bool force_overwrite, bool interactive)
{
    // Check files by loading the config as Modification
    QString mod_config_path = dir.absoluteFilePath("mod.json");
    QFile mod_file(mod_config_path);

    if(!mod_file.open(QFile::ReadOnly))
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Cannot open mod.json! Skipping");

        return false;
    }

    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(mod_file.readAll(), &error);

    if(error.error != QJsonParseError::NoError)
    {        
        getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Loading JSON failed: " + error.errorString());
        return false;
    }

    Modification * mod = Modification::loadFromJson(this, dir.absolutePath(), json.object());

    if(mod == nullptr)
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Loading mod failed!");
        return false;
    }

    QString mod_id = mod->id();
    mod->deleteLater();

    // Copy to correct directory
    QDir destination = profile()->profileModDir().absoluteFilePath(mod_id);

    if(destination.exists())
    {
        getLogger().log(Logger::Warning, "modmanager", "modmanager", "add-mod", "Folder already existing!");

        if(!force_overwrite)
        {
            if(interactive)
            {
                if(QMessageBox::question(nullptr, "Add mod", "There's already a mod with the same unique identifier! Do you want to replace it?") == QMessageBox::No)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }

    destination.removeRecursively();
    destination.mkpath(".");

    utils::copyDirectoryProgress(dir.absolutePath(), destination.absolutePath(), true);

    // Now load mod from destination
    loadMod(destination);
    sortMods();
    m_dependencyTree->rebuildTree();

    // Deactivate it
    getLogger().log(Logger::Info, "modmanager", "modmanager", "add-mod", "Deactivating mod as it was recently installed.");
    mod = getModification(mod_id);
    if(mod != nullptr)
    {
        mod->disableAll();
    }

    return true;
}

bool ModManager::importModFromZip(const QString &filename, bool force_overwrite, bool interactive)
{
    getLogger().log(Logger::Info, "modmanager", "modmanager", "add-mod", "Trying to add mod " + filename);

    QTemporaryDir temp;

    if(temp.isValid())
    {
        QStringList extractedfiles = JlCompress::extractDir(filename, temp.path());

        if(extractedfiles.isEmpty())
        {
            getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Extraction failed!");
            return false;
        }

        return importModFromDirectory(temp.path(), force_overwrite, interactive);
    }
    else
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Could not create temp. dir");
        return false;
    }
}

bool ModManager::importDefaultMods(bool force_overwrite, bool interactive)
{
    // Fetch default mod list
    QStringList files;

    for(QFileInfo info : QDir( QApplication::applicationDirPath() + "/defaultmods").entryInfoList(QDir::Files))
    {
        if(info.fileName().endsWith(".zip"))
        {
            files << info.absoluteFilePath();
        }
    }

    if(files.isEmpty() && interactive)
    {
        QMessageBox::information(nullptr, "Add default mods", "No default mods found.");
        return false;
    }

    bool ret = true;

    for(QString f : files)
    {
        ret &= importModFromZip(f, force_overwrite, interactive);
    }

    return ret;
}

void ModManager::deleteMod(Modification *mod)
{
    if(mod == nullptr)
        throw std::invalid_argument("Cannot find mod id");

    getLogger().log(Logger::Info, "modmanager", "modmanager", "delete-mod", "Starting to remove mod " + mod->id());

    // Deactivate it
    mod->disableAll();

    // Get rid of the directory
    getLogger().log(Logger::Info, "modmanager", "modmanager", "delete-mod", "Removing mod directory " + mod->modBasePath().absolutePath());

    if(!mod->modBasePath().removeRecursively())
    {
        getLogger().log(Logger::Warning, "modmanager", "modmanager", "delete-mod", "Could not remove directory " + mod->modBasePath().absolutePath());
    }

    // Free the mod and unload everything
    m_modId.remove(mod->id());
    m_mods.removeAll(mod);

    delete mod;

    // Re-define priorities and reload mod list
    sortMods();
    m_dependencyTree->rebuildTree();
}

void ModManager::copyModTo(Modification *mod, Profile *p)
{
    if(mod == nullptr)
        throw std::invalid_argument("Cannot find mod id");

    getLogger().log(Logger::Info, "modmanager", "modmanager", "copy-mod", "Started to copy mod " + mod->id() + " to " + p->id());

    QDir destination = p->profileModDir().absoluteFilePath(mod->id());
    destination.removeRecursively();

    utils::copyDirectory(mod->modBasePath(), destination, true);

    getLogger().log(Logger::Info, "modmanager", "modmanager", "copy-mod", "Finished");

    p->getModManager()->loadMod(destination);
    p->getModManager()->sortMods();
    m_dependencyTree->rebuildTree();
}

QString ModManager::unifyModId(QString id)
{
    id = utils::makeValidModId(id);

    if(getModification(id) == nullptr)
        return id;

    // Unify it
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);


    QString as_uid;

    while(as_uid.isEmpty() || m_modId.contains(id + "-" + as_uid))
    {
        as_uid = QString::number(dis(gen));
    }

    return id + "-" + as_uid;
}

QStringList ModManager::installedFiles()
{
    QStringList result;

    for(Modification * mod : m_mods)
    {
        result << mod->installedFiles();
    }

    return result;
}

void ModManager::install()
{
    for(Modification * mod : m_mods)
    {
        mod->install();
    }
}

void ModManager::uninstall()
{
    for(Modification * mod : m_mods)
    {
        mod->uninstall();
    }
}

QString ModManager::autoResolveModUrls(QString content)
{
    content = content.replace("stardewvalley://", profile()->StardewValleyDir().absolutePath() + "/");
    content = content.replace("stardewvalley-savegames://", profile()->StardewValleySavegameDir().absolutePath() + "/");
    content = content.replace("stardewvalley-userdata://", profile()->StardewValleyUserDataDir().absolutePath() + "/");
    content = content.replace("stardewvalley-content://", profile()->StardewValleyContentDir().absolutePath() + "/");

    for(Modification * mod : m_mods)
    {
        // Resolve provides
        if(mod->isPartiallyEnabled())
        {
            // Modid provides @modprovides://path to abspath
            for(QString prov : mod->getProvides())
            {
                content = content.replace("@" + prov + "://", mod->modBasePath().absolutePath() + "/");
            }

            // Content provides abspath/@contentid -> abspath/contentdir
            for(Pipeline * pip : mod->getPipelines())
            {
                for(QString prov : pip->getProvides())
                {
                    content = content.replace(mod->modBasePath().absolutePath() + "/@" + prov, mod->modBasePath().absolutePath() + "/" + pip->id());
                }
            }
        }


        content = content.replace(mod->id() + "://", mod->modBasePath().absolutePath() + "/");
    }    


    return content;
}

QString ModManager::resolveModUrl(const QString &url, bool emptyoninvalid)
{
    if(!url.contains("://"))
        return emptyoninvalid ? "" : url;
    if(url.contains("..") && GlobalSettings::instance()->getEnableFileGuard())
        return emptyoninvalid ? "" : url;

    QString modid = url.split("://")[0];
    QString path = url.split("://")[1];

    // Resolve modid provides
    if(modid.startsWith("@"))
    {
        modid = modid.mid(1);

        for(Modification * mod : getPartiallyActiveMods())
        {
            if(mod->getProvides().contains(modid))
            {
                modid = mod->id();
                break;
            }
        }
    }

    if(modid == "stardewvalley")
    {
        return profile()->StardewValleyDir().absolutePath() + "/" + path;
    }
    else if(modid == "stardewvalley-savegames")
    {
        return profile()->StardewValleySavegameDir().absolutePath() + "/" + path;
    }
    else if(modid == "stardewvalley-userdata")
    {
        return profile()->StardewValleyUserDataDir().absolutePath() + "/" + path;
    }
    else if(modid == "stardewvalley-content")
    {
        return profile()->StardewValleyContentDir().absolutePath() + "/" + path;
    }
    else
    {
         Modification * mod = getModification(modid);

         if(mod == nullptr)
             return emptyoninvalid ? "" : url;

         //Resolve path provides
         if(path.startsWith("@"))
         {
             path = path.mid(1);
             QString prov = path.contains("/") ? path.mid(0, path.indexOf('/')) : path;

             for(Pipeline * pip : mod->getPipelines())
             {
                 if(pip->isEnabled() && pip->getProvides().contains(prov))
                 {
                     path = path.mid(prov.length());
                     path = pip->id() + path;

                     break;
                 }
             }
         }

         return mod->modBasePath().absolutePath() + "/" + path;
    }
}

bool ModManager::isValidModUrl(const QString &url)
{
    if(!url.contains("://"))
        return false;
    if(url.contains("..") && GlobalSettings::instance()->getEnableFileGuard())
        return false;

    QString modid = url.split("://")[0];

    // Resolve modid provides
    if(modid.startsWith("@"))
    {
        modid = modid.mid(1);

        for(Modification * mod : getPartiallyActiveMods())
        {
            if(mod->getProvides().contains(modid))
            {
                modid = mod->id();
                break;
            }
        }
    }

    if(modid == "stardewvalley")
    {
        return true;
    }
    else if(modid == "stardewvalley-savegames")
    {
        return true;
    }
    else if(modid == "stardewvalley-userdata")
    {
        return true;
    }
    else if(modid == "stardewvalley-content")
    {
        return true;
    }
    else
    {
         Modification * mod = getModification(modid);

         if(mod == nullptr)
             return false;
         return true;
    }
}

QString ModManager::toModUrl(const QString &filepath)
{
    QString url;

    if(!(url = utils::toModURL(profile()->StardewValleyContentDir(), filepath, "stardewvalley-content")).isEmpty())
        return url;
    if(!(url = utils::toModURL(profile()->StardewValleyDir(), filepath, "stardewvalley")).isEmpty())
        return url;
    if(!(url = utils::toModURL(profile()->StardewValleySavegameDir(), filepath, "stardewvalley-savegames")).isEmpty())
        return url;
    if(!(url = utils::toModURL(profile()->StardewValleyUserDataDir(), filepath, "stardewvalley-userdata")).isEmpty())
        return url;

    for(Modification * mod : m_mods)
    {
        if(!(url = utils::toModURL(mod->modBasePath(), filepath, mod->id())).isEmpty())
            return url;
    }

    return "";
}

bool ModManager::loadMod(const QDir &directory)
{
    m_unloadableModPaths.removeAll(directory.absolutePath());

    getLogger().log(Logger::Info, "modmanager", "modmanager", "load-mod", "Trying to load mod in " + directory.absolutePath());

    QString mod_config_path = directory.absoluteFilePath("mod.json");

    if(!QFileInfo(mod_config_path).exists())
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Cannot find mod.json! Skipping");
        m_unloadableModPaths << directory.absolutePath();
        return false;
    }

    QFile mod_file(mod_config_path);

    if(!mod_file.open(QFile::ReadOnly))
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Cannot open mod.json! Skipping");
        m_unloadableModPaths << directory.absolutePath();
        return false;
    }

    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(mod_file.readAll(), &error);

    if(error.error != QJsonParseError::NoError)
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Error while parsing JSON! Skipping!");
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "json error: " + error.errorString());
        m_unloadableModPaths << directory.absolutePath();
        return false;
    }

    if(json.isEmpty())
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "JSON is empty! Skipping!");
        m_unloadableModPaths << directory.absolutePath();
        return false;
    }

    Modification * mod = Modification::loadFromJson(this, directory, json.object());

    if(mod != nullptr)
    {
        if(m_modId.contains(mod->id()))
        {
            getLogger().log(Logger::Warning, "modmanager", "modmanager", "load-mod", "Conflicting mod IDs: Will overwrite " + mod->id());

            m_mods.removeAll(getModification(mod->id()));
        }
        else
        {
            getLogger().log(Logger::Info, "modmanager", "modmanager", "load-mod", "Mod " + mod->id() + " loaded in profile " + m_profile->id());

        }

        m_mods.append(mod);
        m_modId.insert(mod->id());
        m_dependencyTree->rebuildTree();
        emit updatedModList();

        return true;
    }
    else
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Could not load mod from JSON!");
        m_unloadableModPaths << directory.absolutePath();
        return false;
    }
}

void ModManager::reloadMods()
{
    for(Modification * mod : m_mods)
    {
        delete mod;
    }
    m_unloadableModPaths.clear();
    m_mods.clear();
    m_modId.clear();

    for(QString entry : m_profile->profileModDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir moddir = m_profile->profileModDir().absoluteFilePath(entry);

       if(!loadMod(moddir))
       {
           getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Loading mod from " + moddir.absolutePath() + " failed!");
       }
    }

    sortMods();
}

void ModManager::sortMods()
{
    m_mods = getModsInPriorityOrder(m_mods);
    m_dependencyTree->rebuildTree();
    emit updatedModList();
}
