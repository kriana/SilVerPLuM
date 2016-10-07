#include "globalsettings.h"
#include "platform.h"

GlobalSettings * GlobalSettings::m_pInstance = nullptr;

GlobalSettings::GlobalSettings()
{
    m_Settings = new QSettings("SilVerPLuM", "SilVerPLuM");
}

GlobalSettings::~GlobalSettings()
{
    delete m_Settings;
}

GlobalSettings *GlobalSettings::instance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new GlobalSettings();
    }

    return m_pInstance;
}

void GlobalSettings::setWindowState(QMainWindow *widget)
{
    m_Settings->setValue("Window/Geometry", widget->saveGeometry());
    m_Settings->setValue("Window/State", widget->saveState());
}

void GlobalSettings::getWindowState(QMainWindow *widget)
{
    widget->restoreGeometry(m_Settings->value("Window/Geometry").toByteArray());
    widget->restoreState(m_Settings->value("Window/State").toByteArray());
}

QString GlobalSettings::getCurrentProfile()
{
    return m_Settings->value("General/CurrentProfile", "").toString();
}

void GlobalSettings::setCurrentProfile(const QString &profileid)
{
    m_Settings->setValue("General/CurrentProfile", profileid);
    m_Settings->sync();
}

bool GlobalSettings::getDLLRedirectXNA()
{
    bool _default = false;

    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
        _default = false;
        break;
    case Platform::Linux:
        _default = true;
        break;
    case Platform::Mac:
        _default = true;
        break;
    }

    return m_Settings->value("Mods/RedirectXNAToMonoGame", _default).toBool();
}

void GlobalSettings::setDLLRedirectXNA(bool enabled)
{
    m_Settings->setValue("Mods/RedirectXNAToMonoGame", enabled);
    m_Settings->sync();
}

bool GlobalSettings::getForceUnsupported()
{
    return m_Settings->value("Mods/ForceUnsupportedMods", false).toBool();
}

void GlobalSettings::setForceUnsupported(bool enabled)
{
    m_Settings->setValue("Mods/ForceUnsupportedMods", enabled);
    m_Settings->sync();
}

bool GlobalSettings::getEnableFileGuard()
{
    return m_Settings->value("Mods/EnableFileGuard", true).toBool();
}

void GlobalSettings::setEnableFileGuard(bool enabled)
{
    m_Settings->setValue("Mods/EnableFileGuard", enabled);
    m_Settings->sync();
}

bool GlobalSettings::getEnableDepencencyCheck()
{
    return m_Settings->value("Mods/EnableDependencyCheck", true).toBool();
}

void GlobalSettings::setEnableDependencyCheck(bool enabled)
{
    m_Settings->setValue("Mods/EnableDependencyCheck", enabled);
    m_Settings->sync();
}

bool GlobalSettings::getEnableDepencyCheckPriorityAwareness()
{
    return m_Settings->value("Mods/EnableDepencyCheckPriorityAwareness", true).toBool();
}

void GlobalSettings::setEnableDepencyCheckPriorityAwareness(bool enabled)
{
    m_Settings->setValue("Mods/EnableDepencyCheckPriorityAwareness", enabled);
    m_Settings->sync();
}

bool GlobalSettings::getRunningBackupSDVSavegames()
{
    return m_Settings->value("Running/BackupSDVSavegames", true).toBool();
}

void GlobalSettings::setRunningBackupSDVSavegames(bool enabled)
{
    m_Settings->setValue("Running/BackupSDVSavegames", enabled);
    m_Settings->sync();
}

bool GlobalSettings::getRunningBackupProfileSavegames()
{
    return m_Settings->value("Running/BackupProfileSavegames", true).toBool();
}

void GlobalSettings::setRunningBackupProfileSavegames(bool enabled)
{
    m_Settings->setValue("Running/BackupProfileSavegames", enabled);
    m_Settings->sync();
}

QString GlobalSettings::getProgramMSBUILD()
{
    QString _default = "";

    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
        _default = "msbuild";
        break;
    case Platform::Linux:
        _default = "xbuild";
        break;
    case Platform::Mac:
        _default = "xbuild";
        break;
    }

    return m_Settings->value("Programs/MSBUILD", _default).toString();
}

void GlobalSettings::setProgramMSBUILD(const QString &program)
{
    m_Settings->setValue("Programs/MSBUILD", program);
    m_Settings->sync();
}

QString GlobalSettings::getProgramNuget()
{
    QString _default = "";

    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
        _default = "nuget";
        break;
    case Platform::Linux:
        _default = "nuget";
        break;
    case Platform::Mac:
        _default = "nuget";
        break;
    }

    return m_Settings->value("Programs/Nuget", _default).toString();
}

void GlobalSettings::setProgramNuget(const QString &program)
{
    m_Settings->setValue("Programs/Nuget", program);
    m_Settings->sync();
}
