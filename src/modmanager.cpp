#include "modmanager.h"
#include "profile.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include "globalsettings.h"
#include <quazip.h>
#include <JlCompress.h>
#include "utils.h"

const QStringList ModManager::FORBIDDEN_MOD_IDS = QStringList() << "stardewvalley" << "stardewvalley-savegames" << "stardewvalley-userdata";

ModManager::ModManager(Profile *profile) : m_profile(profile)
{
    m_config = new QSettings(profile->profileBaseDir().absoluteFilePath("mod-config.ini"), QSettings::IniFormat);

    // Issue dependency check if a profile settings changes
    connect(profile, SIGNAL(updatedSettings()), this, SLOT(issueDependencyCheck()));
}

ModManager::~ModManager()
{
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

Modification *ModManager::getModification(const QString &id)
{
    for(Modification * mod : m_mods)
    {
        if(mod->id() == id)
            return mod;
    }

    return nullptr;
}

Pipeline *ModManager::getPipeline(const QString &mod, const QString &content)
{
    Modification * m = getModification(mod);
    return m->getPipeline(content);
}

int ModManager::setEnabled(const QString &mod, const QString &content, bool enabled)
{
    Pipeline * p = getPipeline(mod, content);

    // If not supported by platform, skip mod
    if(p->unsupported() && !GlobalSettings::instance()->getForceUnsupported())
        return -1;

    m_config->setValue(mod + "/content/" + content, enabled);

    int err = 0;

    if(enabled)
    {
        err = getPipeline(mod, content)->primePipeline(false);
    }

    emit updatedModStatus(mod, content, enabled);
    issueDependencyCheck();

    return err;
}

bool ModManager::isEnabled(const QString &mod, const QString &content)
{
    return m_config->value(mod + "/content/" + content, false).toBool();
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

bool ModManager::priotizeUp(const QString &mod)
{
    Modification * m = getModification(mod);
    int index = m_mods.indexOf(m);

    if(index > 0)
    {
        Modification * t = m_mods[index - 1];
        m_mods[index - 1] = m_mods[index];
        m_mods[index] = t;

        writePriorities();

        emit updatedModList();
        issueDependencyCheck();
        return true;
    }

    return false;
}

bool ModManager::priotizeDown(const QString &mod)
{
    Modification * m = getModification(mod);
    int index = m_mods.indexOf(m);

    if(index < m_mods.size() - 1)
    {
        Modification * t = m_mods[index + 1];
        m_mods[index + 1] = m_mods[index];
        m_mods[index] = t;

        writePriorities();

        emit updatedModList();
        issueDependencyCheck();
        return true;
    }

    return false;
}

bool ModManager::dependencySatisfied(const Dependency &dep, Modification * requester, bool priorityaware)
{
    // Meta dependencies
    if(dep.getId() == "stardewvalley")
    {
        QVersionNumber sdvv = m_profile->StardewValleyVersion();

        if(sdvv.majorVersion() == 0)
            return true;
        else
            return dep.satisfies("stardewvalley", sdvv);
    }

    // Mod dependencies
    for(Modification * mod : m_mods)
    {
        if(!mod->isPartiallyEnabled())
            continue;

        if(dep.satisfies(mod))
            return true;

        if(priorityaware && requester == mod)
        {
            // We require an already INSTALLED mod
            // Cancel here
            break;
        }
    }

    return false;
}

void ModManager::issueDependencyCheck()
{
    m_unsatisfiedDependencies.clear();


    if(GlobalSettings::instance()->getEnableDepencencyCheck())
    {
        bool priorityaware = GlobalSettings::instance()->getEnableDepencyCheckPriorityAwareness();

        for(Modification * tocheck : m_mods)
        {
            if(!tocheck->isPartiallyEnabled())
                continue;

            QList<Dependency> unsatisfied;

            for(Dependency * dep : tocheck->dependencies())
            {
                if(!dependencySatisfied(*dep, tocheck, priorityaware))
                {
                    unsatisfied << *dep;
                }
            }

            if(!unsatisfied.isEmpty())
                m_unsatisfiedDependencies[tocheck->id()] = unsatisfied;
        }
    }

    emit updatedDependencyCheck();
}

Logger &ModManager::getLogger()
{
    return m_logger;
}

bool ModManager::addMod(const QString &filename)
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

        // Check files by loading the config as Modification
        QString mod_config_path = QDir(temp.path()).absoluteFilePath("mod.json");
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
            getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Loading JSON failed!");
            return false;
        }

        Modification * mod = Modification::loadFromJson(this, temp.path(), json.object());

        if(mod == nullptr)
        {
            getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Loading mod failed!");
            return false;
        }

        QString mod_id = mod->id();
        delete mod;

        // Copy to correct directory
        QDir destination = profile()->profileModDir().absoluteFilePath(mod_id);

        if(destination.exists())
        {
            getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Cannot copy: Folder already existing!");

            return false;
        }

        utils::copyDirectoryProgress(temp.path(), destination.absolutePath(), true);

        // Now load mod from destination
        loadMod(destination);
        sortMods();

        return true;
    }
    else
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "add-mod", "Could not create temp. dir");
        return false;
    }
}

void ModManager::deleteMod(const QString &modid)
{
    Modification * mod = getModification(modid);

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
}

void ModManager::copyModTo(const QString &modid, Profile *p)
{
    Modification * mod = getModification(modid);

    if(mod == nullptr)
        throw std::invalid_argument("Cannot find mod id");

    getLogger().log(Logger::Info, "modmanager", "modmanager", "copy-mod", "Started to copy mod " + modid + " to " + p->id());

    QDir destination = p->profileModDir().absoluteFilePath(mod->id());
    destination.removeRecursively();

    utils::copyDirectory(mod->modBasePath(), destination, true);

    getLogger().log(Logger::Info, "modmanager", "modmanager", "copy-mod", "Finished");

    // Evil
    p->getModManager()->loadMod(destination);
    p->getModManager()->sortMods();
}

QMap<QString, QList<Dependency> > ModManager::getUnsatisfiedDependencies() const
{
    return m_unsatisfiedDependencies;
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

    for(Modification * mod : m_mods)
    {
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
    else
    {
         Modification * mod = getModification(modid);

         if(mod == nullptr)
             return emptyoninvalid ? "" : url;
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
    else
    {
         Modification * mod = getModification(modid);

         if(mod == nullptr)
             return false;
         return true;
    }
}

bool ModManager::loadMod(const QDir &directory)
{
    getLogger().log(Logger::Info, "modmanager", "modmanager", "load-mod", "Trying to load mod in " + directory.absolutePath());

    QString mod_config_path = directory.absoluteFilePath("mod.json");

    if(!QFileInfo(mod_config_path).exists())
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Cannot find mod.json! Skipping");

        return false;
    }

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
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Error while parsing JSON! Skipping!");
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "json error: " + error.errorString());

        return false;
    }

    if(json.isEmpty())
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "JSON is empty! Skipping!");
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
        emit updatedModList();

        return true;
    }
    else
    {
        getLogger().log(Logger::Error, "modmanager", "modmanager", "load-mod", "Could not load mod from JSON!");
        return false;
    }
}

void ModManager::reloadMods()
{
    for(Modification * mod : m_mods)
    {
        delete mod;
    }
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
    std::sort(m_mods.begin(), m_mods.end(), [&](Modification * a, Modification * b) {
        return getSortPriority(a->id()) < getSortPriority(b->id());
    });
    emit updatedModList();

    issueDependencyCheck();
}
