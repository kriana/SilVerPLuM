#include "profile.h"
#include <QStandardPaths>
#include <QDebug>
#include "platform.h"
#include "utils.h"
#include "profilemanager.h"

QString Profile::DEFAULT_PROFILE_NAME = "Default";
QString Profile::DEFAULT_PROFILE_ID = "default";

Profile::Profile(const QString &id) : m_Id(id)
{
    m_modManager = new ModManager(this);
    m_savegameManager = new SavegameManager(this);
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
    m_Settings->sync();

    emit updated();
}

QString Profile::description() const
{
    return m_Settings->value("General/Description", "").toString();
}

void Profile::setDescription(const QString &desc)
{
    m_Settings->setValue("General/Description", desc);
    m_Settings->sync();

    emit updated();
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
    m_Settings->sync();

    emit updated();
}

QDir Profile::StardewValleySavegameDir()
{
    return m_Settings->value("StardewValley/SavegameDir", DefaultStardewValleySavegameDir().absolutePath()).toString();
}

void Profile::setStardewValleySavegameDir(const QDir &dir)
{
    m_Settings->setValue("StardewValley/SavegameDir", dir.absolutePath());
    m_Settings->sync();

    emit updated();

    // Trigger savegame list reload
    getSavegameManager()->reloadSavegames();
}

QVersionNumber Profile::StardewValleyVersion()
{
    return QVersionNumber::fromString(m_Settings->value("StardewValley/Version", "0").toString());
}

void Profile::setStardewValleyVersion(const QVersionNumber &version)
{
    m_Settings->setValue("StardewValley/Version", version.toString());
    m_Settings->sync();

    emit updated();
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
    m_Settings->sync();

    emit updated();
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
        getLogger().log(Logger::ERROR, "profiles", "profile", "init", "Cannot create profile outside profile manager!");
        throw std::runtime_error("Cannot create profile outside profile manager!");
    }

    QDir basedir = profileBaseDir();
    QDir profilesavegamedir = basedir.absoluteFilePath("savegames");

    m_Settings = new QSettings(basedir.absoluteFilePath("profile.ini"), QSettings::IniFormat);

    getLogger().log(Logger::INFO, "profiles", "profile", "init", "Initializing profile " + m_Id + " in " + basedir.absolutePath());

    if(!basedir.exists())
    {
        getLogger().log(Logger::INFO, "profiles", "profile", "init", "Initializing profile directory the first time for " + m_Id);

        // Initialize directory
        repairDirectories();

        // If its a default profile, copy savegames to this profile
        if(m_Id == DEFAULT_PROFILE_ID)
        {
            getLogger().log(Logger::INFO, "profiles", "profile", "init", "Profile is default profile. Copying savegames.");

            QDir savegamedir = StardewValleySavegameDir();

            for(QString savegame : savegamedir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
            {
                qInfo() << savegame;

                utils::copyDirectory(savegamedir.absoluteFilePath(savegame), profilesavegamedir.absoluteFilePath(savegame), true);
            }
        }

        setName(m_Id);
        m_Settings->sync();
    }
    else
    {
        repairDirectories();
    }

    // Initialize all mod-related stuff
    m_modManager->initialize();

    // Initialize savegame manager
    m_savegameManager->initialize();

    // Build launchers
    m_Launchers.append(new VanillaLauncher(this));
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
    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
        return QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)).filePath("StardewValley\\Saves");
    case Platform::Linux:
        return QDir(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)).filePath("StardewValley/Saves");
    case Platform::Mac:
        return QDir(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)).filePath("StardewValley/Saves");
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
