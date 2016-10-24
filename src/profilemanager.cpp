#include "profilemanager.h"
#include <QRegExp>
#include <QStandardPaths>
#include "utils.h"
#include "globalsettings.h"
#include <JlCompress.h>

ProfileManager * ProfileManager::m_pInstance = nullptr;

ProfileManager *ProfileManager::instance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new ProfileManager();
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
    if(m_initialized)
        throw std::runtime_error("Profile manager is already initialized!");

    getLogger().log(Logger::Info, "program", "program", "arguments", utils::ArgumentListToString(QApplication::arguments()));

    // Look for existing profiles
    if(ProfilesDir().exists())
    {
        for(QString id : ProfilesDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            if(!idExists(id))
                createOrLoadProfile(id);
        }
    }

    if(m_Profiles.empty() || getProfile(Profile::DEFAULT_PROFILE_ID) == nullptr)
        createOrLoadProfile(Profile::DEFAULT_PROFILE_ID, Profile::DEFAULT_PROFILE_NAME);

    Profile * current_by_setting = getProfile(GlobalSettings::instance()->getCurrentProfile());

    m_initialized = true;

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
    QString id = utils::makeValidModId(name);

    return createOrLoadProfile(id, name);
}

Profile *ProfileManager::createOrLoadProfile(const QString &id, const QString &name)
{   
    if(!utils::isValidModId(id))
    {
        getLogger().log(Logger::Warning, "profiles", "manager", "create-or-load", "Invalid ID " + id);
        return nullptr;
    }
    if(idExists(id))
    {
        getLogger().log(Logger::Warning, "profiles", "manager", "create-or-load", "ID alread exists: " + id);
        return nullptr;
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
    connect(p, SIGNAL(updatedSettings()), this, SIGNAL(updatedProfileSetting()));
    emit updated();
    emit updatedProfileList();

    if(!load && GlobalSettings::instance()->getAutoAddDefaultMods())
    {
        p->getModManager()->importDefaultMods(false, false);
    }

    return p;
}

bool ProfileManager::deleteProfile(Profile *p)
{
    if(p == nullptr || !m_Profiles.contains(p))
    {
        getLogger().log(Logger::Warning, "profiles", "manager", "delete", "Unknown profile");
        return false;
    }
    if(p->id() == Profile::DEFAULT_PROFILE_ID)
    {
        getLogger().log(Logger::Warning, "profiles", "manager", "delete", "Cannot delete default profile");
        return false;
    }

    if(m_SelectedProfile == p)
        selectProfile(m_Profiles.first());

    disconnect(p, &Profile::updated, this, &ProfileManager::updated);

    m_Profiles.removeAll(p);
    p->profileBaseDir().removeRecursively();

    delete p;
    emit updated();
    emit updatedProfileList();

    return true;
}

bool ProfileManager::duplicateProfile(Profile *p, const QString &name)
{
    QString id = utils::makeValidModId(name);

    if(idExists(id))
    {
        getLogger().log(Logger::Warning, "profiles", "manager", "duplicate", "ID alread exists: " + id);
        return false;
    }

    utils::copyDirectoryProgress(p->profileBaseDir(), ProfilesDir().absoluteFilePath(id), true);
    createOrLoadProfile(id, name);

    // Change the profile's name
    Profile * np = getProfile(id);

    if(np != nullptr)
    {
        np->setName(name);
    }

    return true;
}

bool ProfileManager::exportProfile(Profile *p, const QString &path)
{
    getLogger().log(Logger::Warning, "profiles", "manager", "export", "Exporting " + p->id() + " to " + path);

    QFile(path).remove();
    if(!JlCompress::compressDir(path, p->profileBaseDir().absolutePath(), true))
    {
        return false;
    }

    return true;
}

bool ProfileManager::importProfile(const QString &path, const QString & name)
{
    QString id = utils::makeValidModId(name);

    if(idExists(id))
    {
        getLogger().log(Logger::Warning, "profiles", "manager", "import", "ID alread exists: " + id);
        return false;
    }

    // Create the directory
    QDir basedir = ProfilesDir().absoluteFilePath(id);
    basedir.mkpath(".");

    // Extract
    getLogger().log(Logger::Warning, "profiles", "manager", "import", "Extracting " + path + " into " + basedir.absolutePath());

    JlCompress::extractDir(path, basedir.absolutePath());

    Profile * p = createOrLoadProfile(id, name);
    p->setName(name);

    return true;
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
    emit updatedSelection(p);
}
