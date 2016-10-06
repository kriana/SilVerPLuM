#include "modmanager.h"
#include "profile.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include "globalsettings.h"

ModManager::ModManager(Profile *profile) : m_profile(profile)
{
    m_config = new QSettings(profile->profileBaseDir().absoluteFilePath("mod-config.ini"), QSettings::IniFormat);

    // Issue dependency check if a profile settings changes
    connect(profile, SIGNAL(updated()), this, SLOT(issueDependencyCheck()));
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
    loadMods();
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

void ModManager::setEnabled(const QString &mod, const QString &content, bool enabled)
{
    Pipeline * p = getPipeline(mod, content);

    // If not supported by platform, skip mod
    if(p->unsupported() && !GlobalSettings::instance()->getForceUnsupported())
        return;

    m_config->setValue(mod + "/content/" + content, enabled);

    if(enabled)
    {
        getPipeline(mod, content)->prime();
    }

    emit modEnabledDisabled(mod, content, enabled);
    issueDependencyCheck();
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

        emit modListUpdated();
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

        emit modListUpdated();
        return true;
    }

    return false;
}

bool ModManager::dependencySatisfied(const Dependency &dep)
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
        if(dep.satisfies(mod))
            return true;
    }

    return false;
}

void ModManager::issueDependencyCheck()
{
    m_unsatisfiedDependencies.clear();

    for(Modification * tocheck : m_mods)
    {
        QList<Dependency> unsatisfied;

        for(Dependency * dep : tocheck->dependencies())
        {
            if(!dependencySatisfied(*dep))
            {
                unsatisfied << *dep;
            }
        }

        if(!unsatisfied.isEmpty())
            m_unsatisfiedDependencies[tocheck->id()] = unsatisfied;
    }

    emit dependencyCheckFinished();
}

Logger &ModManager::getLogger()
{
    return m_logger;
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

QString ModManager::resolveModUrl(const QString &url)
{
    if(!url.contains("://"))
        return "";
    if(url.contains("..") && GlobalSettings::instance()->getEnableFileGuard())
        return "";

    QString modid = url.split("://")[0];
    QString path = url.split("://")[1];

    if(modid != "stardewvalley")
    {
         Modification * mod = getModification(modid);

         if(mod == nullptr)
             return "";
         return mod->modBasePath().absolutePath() + "/" + path;
    }
    else
    {
        return profile()->StardewValleyDir().absolutePath() + "/" + path;
    }
}

void ModManager::loadMod(const QDir &directory)
{
    getLogger().log(Logger::INFO, "modmanager", "modmanager", "load-mod", "Trying to load mod in " + directory.absolutePath());

    QString mod_config_path = directory.absoluteFilePath("mod.json");

    if(!QFileInfo(mod_config_path).exists())
    {
        getLogger().log(Logger::ERROR, "modmanager", "modmanager", "load-mod", "Cannot find mod.json! Skipping");

        return;
    }

    QFile mod_file(mod_config_path);

    if(!mod_file.open(QFile::ReadOnly))
    {
        getLogger().log(Logger::ERROR, "modmanager", "modmanager", "load-mod", "Cannot open mod.json! Skipping");

        return;
    }

    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(mod_file.readAll(), &error);

    if(error.error != QJsonParseError::NoError)
    {
        getLogger().log(Logger::ERROR, "modmanager", "modmanager", "load-mod", "Error while parsing JSON! Skipping!");
        getLogger().log(Logger::ERROR, "modmanager", "modmanager", "load-mod", "json error: " + error.errorString());

        return;
    }

    if(json.isEmpty())
    {
        getLogger().log(Logger::ERROR, "modmanager", "modmanager", "load-mod", "JSON is empty! Skipping!");
        return;
    }

    Modification * mod = nullptr;

    try
    {
        mod = Modification::loadFromJson(this, directory, json.object());
    }
    catch(...)
    {

    }

    if(mod != nullptr)
    {
        if(m_modId.contains(mod->id()))
        {
            getLogger().log(Logger::WARNING, "modmanager", "modmanager", "load-mod", "Conflicting mod IDs: Will overwrite " + mod->id());

            m_mods.removeAll(getModification(mod->id()));
        }
        else
        {
            getLogger().log(Logger::INFO, "modmanager", "modmanager", "load-mod", "Mod " + mod->id() + " loaded in profile " + m_profile->id());

        }

        m_mods.append(mod);
        m_modId.insert(mod->id());
        emit modListUpdated();
    }
    else
    {
        getLogger().log(Logger::ERROR, "modmanager", "modmanager", "load-mod", "Could not load mod from JSON!");
    }
}

void ModManager::loadMods()
{
    for(QString entry : m_profile->profileModDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir moddir = m_profile->profileModDir().absoluteFilePath(entry);

        try
        {
            loadMod(moddir);
        }
        catch(...)
        {
            getLogger().log(Logger::ERROR, "modmanager", "modmanager", "load-mod", "Loading mod from " + moddir.absolutePath() + " failed!");
        }
    }

    sortMods();
}

void ModManager::sortMods()
{
    std::sort(m_mods.begin(), m_mods.end(), [&](Modification * a, Modification * b) {
        return getSortPriority(a->id()) < getSortPriority(b->id());
    });
    emit modListUpdated();

    issueDependencyCheck();
}
