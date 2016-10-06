#include "profilemanager.h"
#include <QRegExp>
#include <QStandardPaths>
#include "utils.h"
#include "globalsettings.h"

ProfileManager * ProfileManager::m_pInstance = nullptr;

ProfileManager *ProfileManager::instance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new ProfileManager();

        m_pInstance->initialize();
    }

    return m_pInstance;
}

ProfileManager::ProfileManager()
{
}

Logger & ProfileManager::getLogger()
{
    return m_logger;
}

ProfileManager::~ProfileManager()
{
    for(Profile * p : m_Profiles)
    {
        delete p;
    }
}

void ProfileManager::initialize()
{
    // Look for existing profiles
    if(ProfilesDir().exists())
    {
        for(QString id : ProfilesDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            if(!idExists(id))
                createOrLoadProfile(id);
        }
    }

    if(m_Profiles.empty())
        createOrLoadProfile(Profile::DEFAULT_PROFILE_ID, Profile::DEFAULT_PROFILE_NAME);

    Profile * current_by_setting = getProfile(GlobalSettings::instance()->getCurrentProfile());

    if(current_by_setting == nullptr)
        selectProfile(m_Profiles.first());
    else
        selectProfile(current_by_setting);
}

QList<Profile *> ProfileManager::getProfiles()
{
    return QList<Profile *>(m_Profiles);
}

Profile *ProfileManager::getProfile(const QString & id)
{
    for(Profile * p : m_Profiles)
    {
        if(p->id() == id)
            return p;
    }

    return nullptr;
}

Profile * ProfileManager::createOrLoadProfile(const QString &name)
{
    QString id = name.toLower().replace(QRegExp("[^a-zA-Z0-9_.]+"), "_");

    return createOrLoadProfile(id, name);
}

Profile *ProfileManager::createOrLoadProfile(const QString &id, const QString &name)
{
    QString id_ = id.toLower().replace(QRegExp("[^a-zA-Z0-9_.]+"), "_");

    if(id_ != id)
    {
        getLogger().log(Logger::WARNING, "profiles", "manager", "create-or-load", "Invalid ID " + id);
        throw std::invalid_argument("Invalid ID!");
    }
    if(idExists(id))
    {
        getLogger().log(Logger::WARNING, "profiles", "manager", "create-or-load", "ID alread exists: " + id);
        throw std::invalid_argument("Profile with same id already exists!");
    }

    Profile * p = new Profile(id);
    m_Profiles.append(p);

    bool load = p->exists();

    p->initialize();

    if(!load)
    {
        p->setName(name);
    }

    connect(p, &Profile::updated, this, &ProfileManager::updated);
    emit updated();

    return p;
}

void ProfileManager::deleteProfile(Profile *p)
{
    if(p == nullptr || !m_Profiles.contains(p))
    {
        getLogger().log(Logger::WARNING, "profiles", "manager", "delete", "Unknown profile");
        throw std::invalid_argument("Profile is unknown!");
    }
    if(p->id() == Profile::DEFAULT_PROFILE_ID)
    {
        getLogger().log(Logger::WARNING, "profiles", "manager", "delete", "Cannot delete default profile");
        throw std::invalid_argument("Cannot remove default profile!");
    }

    if(m_SelectedProfile == p)
        selectProfile(m_Profiles.first());

    disconnect(p, &Profile::updated, this, &ProfileManager::updated);

    m_Profiles.removeAll(p);
    p->profileBaseDir().removeRecursively();

    delete p;
    emit updated();
}

void ProfileManager::duplicateProfile(Profile *p, const QString &name)
{
    QString id = name.toLower().replace(QRegExp("[^a-zA-Z0-9_.]+"), "_");

    if(idExists(id))
    {
        getLogger().log(Logger::WARNING, "profiles", "manager", "duplicate", "ID alread exists: " + id);
        throw std::invalid_argument("ID already exists!");
    }

    utils::copyDirectoryProgress(p->profileBaseDir(), ProfilesDir().absoluteFilePath(id), true);
    createOrLoadProfile(id, name);

    // Change the profile's name
    Profile * np = getProfile(id);

    if(np!=nullptr)
    {
        np->setName(name);
    }
}

bool ProfileManager::idExists(const QString &id)
{
    for(Profile * p : m_Profiles)
    {
        if(p->id() == id)
            return true;
    }

    return false;
}

QDir ProfileManager::ProfilesDir()
{
    return QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("profiles");
}

Profile *ProfileManager::getSelectedProfile()
{
    return m_SelectedProfile;
}

void ProfileManager::selectProfile(Profile *p)
{
    if(p == nullptr || !m_Profiles.contains(p))
        p = m_Profiles.first();

    if(p == m_SelectedProfile)
        return;

    m_SelectedProfile = p;
    GlobalSettings::instance()->setCurrentProfile(p->id());
    emit selected(p);
}
