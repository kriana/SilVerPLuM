#include "modmanager.h"
#include "profile.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

ModManager::ModManager(Profile *profile) : m_profile(profile)
{
    m_config = new QSettings(profile->profileBaseDir().absoluteFilePath("mod-config.ini"), QSettings::IniFormat);
}

ModManager::~ModManager()
{
    for(Modification * mod : m_mods.values())
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

Modification *ModManager::getModification(const QString &mod)
{
    return m_mods[mod];
}

Pipeline *ModManager::getPipeline(const QString &mod, const QString &content)
{
    Modification * m = getModification(mod);
    return m->getPipeline(content);
}

void ModManager::setEnabled(const QString &mod, const QString &content, bool enabled)
{
    m_config->setValue(mod + "/" + content, enabled);

    if(enabled)
    {
        getPipeline(mod, content)->prime();
    }
}

bool ModManager::isEnabled(const QString &mod, const QString &content)
{
    return m_config->value(mod + "/" + content, false).toBool();
}

void ModManager::loadMod(const QDir &directory)
{
    qInfo() << "Trying to load mod in " << directory.absolutePath();

    QString mod_config_path = directory.absoluteFilePath("mod.json");

    if(!QFileInfo(mod_config_path).exists())
    {
        qWarning() << "Cannot find mod.json! Skipping";
        return;
    }

    QFile mod_file(mod_config_path);

    if(!mod_file.open(QFile::ReadOnly))
    {
        qWarning() << "Cannot open mod.json! Skipping";
        return;
    }

    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(mod_file.readAll(), &error);

    if(error.error != QJsonParseError::NoError)
    {
        qWarning() << "Error while parsing JSON! Skipping!";
        qWarning() << error.errorString();
        return;
    }

    if(json.isEmpty())
    {
        qWarning() << "JSON is empty! Skipping!";
        return;
    }

    Modification * mod = nullptr;

    try
    {
        mod = Modification::loadFromJson(this, json.object());
    }
    catch(...)
    {

    }

    if(mod != nullptr)
    {
        if(m_mods.contains(mod->getId()))
        {
            qWarning() << "Conflicting mod IDs: Will overwrite " << mod->getId();
        }
        else
        {
            qInfo() << "Mod " << mod->getId() << " loaded in profile " << m_profile->id();
        }

        m_mods[mod->getId()] = mod;
    }
    else
    {
        qWarning() << "Could not load mod from JSON!";
    }
}

void ModManager::loadMods()
{
    for(QString entry : m_profile->profileModDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir moddir = m_profile->profileModDir().absoluteFilePath(entry);

        loadMod(moddir);
    }
}
