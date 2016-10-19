#include "profile.h"
#include <QStandardPaths>
#include <QDebug>
#include "platform.h"
#include "utils.h"
#include "profilemanager.h"
#include "debuglauncher.h"

QString Profile::DEFAULT_PROFILE_NAME = "Default";
QString Profile::DEFAULT_PROFILE_ID = "default";

Profile::Profile(const QString &id) : m_Id(id)
{
    m_modManager = new ModManager(this);
    m_savegameManager = new SavegameManager(this);

    connect(m_modManager, SIGNAL(updatedModList()), this, SIGNAL(updated()));
    connect(m_modManager, SIGNAL(updatedModStatus(QString,QString,bool)), this, SIGNAL(updated()));
    connect(m_modManager, SIGNAL(updatedDependencyCheck()), this, SIGNAL(updated()));
    connect(m_modManager, SIGNAL(updatedModList()), this, SIGNAL(updatedMods()));
    connect(m_modManager, SIGNAL(updatedModStatus(QString,QString,bool)), this, SIGNAL(updatedMods()));
    connect(m_modManager, SIGNAL(updatedDependencyCheck()), this, SIGNAL(updatedMods()));

    connect(m_savegameManager, SIGNAL(updatedSavegames()), this, SIGNAL(updated()));
    connect(m_savegameManager, SIGNAL(updatedSavegames()), this, SIGNAL(updatedSavegames()));
}

Profile::~Profile()
{
    delete m_Settings;

    for(Launcher * l : m_Launchers)
    {
        delete l;
    }

    delete m_savegameManager;
    delete m_modManager;
}

QString Profile::id() const
{
    return m_Id;
}

QString Profile::name() const
{
    return m_Settings->value("General/Name", id()).toString();
}

void Profile::setName(const QString &name)
{
    m_Settings->setValue("General/Name", name);

    setting_changed();
}

QString Profile::description() const
{
    return m_Settings->value("General/Description", "").toString();
}

void Profile::setDescription(const QString &desc)
{
    m_Settings->setValue("General/Description", desc);

    setting_changed();
}

QDir Profile::profileBaseDir()
{
    return ProfileManager::ProfilesDir().filePath(m_Id);
}

QDir Profile::profileSavegameDir()
{
    return profileBaseDir().absoluteFilePath("savegames");
}

QDir Profile::profileSavegameBackupDir()
{
    return profileBaseDir().absoluteFilePath("savegame-backups");
}

QDir Profile::profileModDir()
{
    return profileBaseDir().absoluteFilePath("mods");
}

QDir Profile::StardewValleyDir()
{
    return m_Settings->value("StardewValley/GameDir", DefaultStardewValleyDir().absolutePath()).toString();
}

void Profile::setStardewValleyDir(const QDir &dir)
{
    m_Settings->setValue("StardewValley/GameDir", dir.absolutePath());

    setting_changed();
}

QDir Profile::StardewValleySavegameDir()
{
    return m_Settings->value("StardewValley/SavegameDir", DefaultStardewValleySavegameDir().absolutePath()).toString();
}

void Profile::setStardewValleySavegameDir(const QDir &dir)
{
    m_Settings->setValue("StardewValley/SavegameDir", dir.absolutePath());

    setting_changed();

    // Trigger savegame list reload
    getSavegameManager()->reloadSavegames();
}

QDir Profile::StardewValleyUserDataDir()
{
    return m_Settings->value("StardewValley/UserDataDir", DefaultStardewValleyUserDataDir().absolutePath()).toString();
}

void Profile::setStardewValleyUserDataDir(const QDir &dir)
{
    m_Settings->setValue("StardewValley/UserDataDir", dir.absolutePath());

    setting_changed();

    // Trigger savegame list reload
    getSavegameManager()->reloadSavegames();
}

QDir Profile::StardewValleyContentDir()
{
    return m_Settings->value("StardewValley/ContentDir", DefaultStardewValleyContentDir().absolutePath()).toString();
}

void Profile::setStardewValleyContentDir(const QDir &dir)
{
    m_Settings->setValue("StardewValley/ContentDir", dir.absolutePath());

    setting_changed();
}

QVersionNumber Profile::StardewValleyVersion()
{
    return QVersionNumber::fromString(m_Settings->value("StardewValley/Version", "0").toString());
}

void Profile::setStardewValleyVersion(const QVersionNumber &version)
{
    m_Settings->setValue("StardewValley/Version", version.toString());

    setting_changed();
}



Platform::GameTechnology Profile::StardewValleyTechnology()
{
    int v = m_Settings->value("StardewValley/GameTechnology", DefaultStardewValleyTechnology()).toInt();

    switch(v)
    {
    case Platform::GameTechnologyXNA:
        return Platform::GameTechnologyXNA;
    case Platform::GameTechnologyMonoGame:
        return Platform::GameTechnologyMonoGame;
    default:
        return Platform::GameTechnologyXNA;
    }
}

void Profile::setStardewValleyTechnology(Platform::GameTechnology tech)
{
    m_Settings->setValue("StardewValley/GameTechnology", tech);

    setting_changed();
}

QString Profile::StardewValleyTechnologyString()
{
    switch(StardewValleyTechnology())
    {
    case Platform::GameTechnologyXNA:
        return "xna";
    case Platform::GameTechnologyMonoGame:
        return "monogame";
    default:
        return "xna";
    }
}

bool Profile::enableBackupOnStart()
{
    return m_Settings->value("Savegames/BackupOnStart", false).toBool();
}

void Profile::setEnableBackupOnStart(bool enabled)
{
    m_Settings->setValue("Savegames/BackupOnStart", enabled);

    setting_changed();
}

bool Profile::checkForExistingBackups()
{
    return m_Settings->value("Savegames/CheckForExistingBackups", true).toBool();
}

void Profile::setCheckForExistingBackups(bool enabled)
{
    m_Settings->setValue("Savegames/CheckForExistingBackups", enabled);

    setting_changed();
}

int Profile::backupInterval()
{
    int i = m_Settings->value("Savegames/BackupInterval", 0).toInt();

    return i >= 0 ? i : 0;
}

void Profile::setBackupInterval(int interval)
{
    m_Settings->setValue("Savegames/BackupInterval", interval >= 0 ? interval : 0);

    setting_changed();
}

bool Profile::exists()
{
    return profileBaseDir().exists();
}

void Profile::setLauncher(const QString &id)
{
    for(Launcher * l : getLaunchers())
    {
        if(l->id() == id)
        {
            m_Settings->setValue("Launcher/Launcher", id);
            return;
        }
    }

    qWarning() << "Unable to set launcher to " << id << " setting it back to vanilla";
    m_Settings->setValue("Launcher/Launcher", VanillaLauncher::ID);
}

Launcher *Profile::getLauncher()
{
    QString lid = m_Settings->value("Launcher/Launcher", VanillaLauncher::ID).toString();

    return getLauncher(lid);
}

Launcher *Profile::getLauncher(const QString &id)
{
    for(Launcher * l : getLaunchers())
    {
        if(l->id() == id)
            return l;
    }

    return m_Launchers.first(); //Always the vanilla launcher
}

QList<Launcher *> Profile::getLaunchers()
{
    QList<Launcher*> result(m_Launchers);

    // Add launchers of enabled pipelines
    for(Modification * mod : m_modManager->getModifications())
    {
        for(Pipeline * pip : mod->getPipelines())
        {
            if(pip->isEnabled())
            {
                for(Launcher * l : pip->launchers())
                {
                    result << l;
                }
            }
        }
    }

    return result;
}

void Profile::repairDirectories()
{
    profileBaseDir().mkpath(".");
    profileModDir().mkpath(".");
    profileSavegameDir().mkpath(".");
    profileSavegameBackupDir().mkpath(".");
}

void Profile::setting_changed()
{
    if(!m_updateBatch)
    {
        m_Settings->sync();
        emit updated();
        emit updatedSettings();
    }
}

bool Profile::getUpdateBatch() const
{
    return m_updateBatch;
}

void Profile::setUpdateBatch(bool updateBatch)
{
    m_updateBatch = updateBatch;
    setting_changed();
}


SavegameManager *Profile::getSavegameManager() const
{
    return m_savegameManager;
}

Logger &Profile::getLogger()
{
    return m_logger;
}

ModManager *Profile::getModManager() const
{
    return m_modManager;
}

void Profile::initialize()
{
    // Guard
    if(!ProfileManager::instance()->getProfiles().contains(this))
    {
        getLogger().log(Logger::Error, "profiles", "profile", "init", "Cannot create profile outside profile manager!");
        throw std::runtime_error("Cannot create profile outside profile manager!");
    }

    QDir basedir = profileBaseDir();
    QDir profilesavegamedir = basedir.absoluteFilePath("savegames");

    m_Settings = new QSettings(basedir.absoluteFilePath("profile.ini"), QSettings::IniFormat);

    getLogger().log(Logger::Info, "profiles", "profile", "init", "Initializing profile " + m_Id + " in " + basedir.absolutePath());

    if(!basedir.exists())
    {
        getLogger().log(Logger::Info, "profiles", "profile", "init", "Initializing profile directory the first time for " + m_Id);

        // Initialize directory
        repairDirectories();

        // If its a default profile, copy savegames to this profile
        if(m_Id == DEFAULT_PROFILE_ID)
        {
            getLogger().log(Logger::Info, "profiles", "profile", "init", "Profile is default profile. Copying savegames.");

            QDir savegamedir = StardewValleySavegameDir();

            for(QString savegame : savegamedir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
            {
                qInfo() << savegame;

                utils::copyDirectory(savegamedir.absoluteFilePath(savegame), profilesavegamedir.absoluteFilePath(savegame), true);
            }

            // Set default description
            setDescription(utils::readAllTextFrom(":/resources/markdown/default.md"));
        }

        setName(m_Id);
        m_Settings->sync();
    }
    else
    {
        repairDirectories();
    }

    // Fix some crazy stuff
    fixCrazyness();

    // Initialize all mod-related stuff
    m_modManager->initialize();

    // Initialize savegame manager
    m_savegameManager->initialize();

    // Build launchers
    m_Launchers.append(new VanillaLauncher(this));
    m_Launchers.append(new DebugLauncher(this));
}

void Profile::fixCrazyness()
{
    // Fix different executable names between Windows <-> Linux. Thank you.
    if( Platform::getCurrentPlatform() == Platform::Windows && QFileInfo(StardewValleyDir().absoluteFilePath("Stardew Valley.exe")).exists())
    {
        getLogger().log(Logger::Info, "profile", "fix-crazyness", "inconsistent-executables", "Why is the executable on Windows called 'Stardew Valley.exe' and on other platforms 'StardewValley.exe'? I'll copy it.");

        QFile(StardewValleyDir().absoluteFilePath("StardewValley.exe")).remove();
        QFile::copy(StardewValleyDir().absoluteFilePath("Stardew Valley.exe"),
                    StardewValleyDir().absoluteFilePath("StardewValley.exe"));
    }
}

QProcessEnvironment Profile::processEnvironment()
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    env.insert("STARDEWVALLEY_DIR", StardewValleyDir().absolutePath());
    env.insert("STARDEWVALLEY_SAVEGAME_DIR", StardewValleySavegameDir().absolutePath());
    env.insert("STARDEWVALLEY_USERDATA_DIR", StardewValleyUserDataDir().absolutePath());
    env.insert("STARDEWVALLEY_CONTENT_DIR", StardewValleyContentDir().absolutePath());
    env.insert("STARDEWVALLEY_PLATFORM", Platform::getPlatformString());
    env.insert("STARDEWVALLEY_TECHNOLOGY", StardewValleyTechnologyString());
    env.insert("STARDEWVALLEY_TOOL", "Silverplum");

    return env;
}

Platform::GameTechnology Profile::DefaultStardewValleyTechnology()
{
    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
        return Platform::GameTechnologyXNA;
    case Platform::Linux:
        return Platform::GameTechnologyMonoGame;
    case Platform::Mac:
        return Platform::GameTechnologyMonoGame;
    default:
        throw std::runtime_error("Unsupported platform!");
    }
}

QDir Profile::DefaultStardewValleySavegameDir()
{
    return DefaultStardewValleyUserDataDir().absoluteFilePath("Saves");
}

QDir Profile::DefaultStardewValleyUserDataDir()
{
    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:

        // Need workaround for Windows as GenericConfigLocation and GenericDataLocation both point to appdata local and not roaming
        {
            QDir loc = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
            loc.cdUp();

            return loc.filePath("StardewValley");
        }

    case Platform::Linux:
        return QDir(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)).filePath("StardewValley");
    case Platform::Mac:
        return QDir(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)).filePath("StardewValley");
    default:
        throw std::runtime_error("Unsupported platform!");
    }
}

QDir Profile::DefaultStardewValleyDir()
{
    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
    {
        QDir opt1("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Stardew Valley\\");
        QDir opt2("C:\\Program Files\\Steam\\steamapps\\common\\Stardew Valley\\");

        if(opt1.exists())
            return opt1;
        return opt2;
    }
    case Platform::Linux:
        return QDir(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).absolutePath() + ("/.local/share/Steam/steamapps/common/Stardew Valley/");
    case Platform::Mac:
        return QDir(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).absolutePath() + ("/Library/Application Support/Steam/steamapps/common/Stardew Valley");
    default:
        throw std::runtime_error("Unsupported platform!");
    }
}

QDir Profile::DefaultStardewValleyContentDir()
{
    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
        return DefaultStardewValleyDir().absoluteFilePath("Content");
    case Platform::Linux:
        return DefaultStardewValleyDir().absoluteFilePath("Content");
    case Platform::Mac:
        throw std::runtime_error("--> Insert here <--");
    default:
        throw std::runtime_error("Unsupported platform!");
    }
}

QStringList Profile::StardewValleyVersions()
{
    QStringList versions;

    versions << "1.1.1";
    versions << "1.1";
    versions << "1.0.7";
    versions << "1.0.6";
    versions << "1.0.5";
    versions << "1.0.4";
    versions << "1.0.3";
    versions << "1.0.2";
    versions << "1.0.1";
    versions << "1.0";
    versions << "0";

    return versions;
}
