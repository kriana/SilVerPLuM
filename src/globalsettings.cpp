#include "globalsettings.h"
#include "platform.h"
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>
#include "utils.h"

GlobalSettings * GlobalSettings::m_pInstance = nullptr;

GlobalSettings::GlobalSettings()
{
    m_Settings = new QSettings("SilVerPLuM", "SilVerPLuM");
}

GlobalSettings::~GlobalSettings()
{
    delete m_Settings;
}

void GlobalSettings::initializeDefaultExternalPrograms()
{
    switch(Platform::getCurrentPlatform())
    {
    case Platform::Windows:
        initializeWindowsExternalPrograms();
        break;
    case Platform::Linux:
        initializeLinuxExternalPrograms();
        break;
    case Platform::Mac:
        initializeMacExternalPrograms();
        break;
    }
}

void GlobalSettings::initializeWindowsExternalPrograms()
{
    m_DefaultExternalPrograms["msbuild"] = ExternalProgram(QStringList() << "C:/Program Files/MSBuild/14.0/Bin/MSBuild.exe"
                                                           << "C:/Program Files (x86)/MSBuild/14.0/Bin/MSBuild.exe",
                                                           QStringList() << "{insertargs}",
                                                           QStringList(),
                                                           true);
    m_DefaultExternalPrograms["nuget"] = ExternalProgram(QStringList() << "nuget.exe",
                                                           QStringList() << "{insertargs}",
                                                           QStringList(),
                                                           true);
}

void GlobalSettings::initializeLinuxExternalPrograms()
{
    m_DefaultExternalPrograms["msbuild"] = ExternalProgram(QStringList() << "/usr/bin/xbuild",
                                                           QStringList() <<"{insertargs}",
                                                           QStringList(),
                                                           true);
    m_DefaultExternalPrograms["nuget"] = ExternalProgram(QStringList() << "/usr/bin/nuget",
                                                           QStringList() << "{insertargs}",
                                                           QStringList(),
                                                         true);
    m_DefaultExternalPrograms["mono"] = ExternalProgram(QStringList() << "/usr/bin/mono",
                                                           QStringList() << "{insertargs}",
                                                           QStringList() << "application/x-ms-dos-executable",
                                                         true);
    m_DefaultExternalPrograms["bash"] = ExternalProgram(QStringList() << "/bin/bash",
                                                           QStringList() << "-c" << "{joinedargs}",
                                                           QStringList() << "application/x-shellscript",
                                                         true);
}

void GlobalSettings::initializeMacExternalPrograms()
{
    m_DefaultExternalPrograms["msbuild"] = ExternalProgram(QStringList() << "/usr/bin/xbuild",
                                                           QStringList() <<"{insertargs}",
                                                           QStringList(),
                                                           true);
    m_DefaultExternalPrograms["nuget"] = ExternalProgram(QStringList() << "/usr/bin/nuget",
                                                           QStringList() << "{insertargs}",
                                                           QStringList(),
                                                         true);
    m_DefaultExternalPrograms["mono"] = ExternalProgram(QStringList() << "/usr/bin/mono",
                                                           QStringList() << "{insertargs}",
                                                           QStringList() << "application/x-ms-dos-executable",
                                                         true);
    m_DefaultExternalPrograms["bash"] = ExternalProgram(QStringList() << "/bin/bash",
                                                           QStringList() << "-c" << "{joinedargs}",
                                                           QStringList() << "application/x-shellscript",
                                                         true);
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
        _default = true;
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

bool GlobalSettings::getEnablePrimeCache()
{
    return m_Settings->value("Mods/EnablePrimeCache", true).toBool();
}

void GlobalSettings::setEnablePrimeCache(bool enabled)
{
    m_Settings->setValue("Mods/EnablePrimeCache", enabled);
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

ExternalProgram GlobalSettings::getExternalProgram(const QString &id)
{
    ExternalProgram default_program = m_DefaultExternalPrograms[id];

    QString executable = m_Settings->value("Programs/" + id + "/Executable", default_program.executablePath()).toString();
    QString argumentString = m_Settings->value("Programs/" + id + "/ArgumentString", utils::ArgumentListToString(default_program.arguments())).toString();
    QString mimetypeString = m_Settings->value("Programs/" + id + "/MimeTypeString", utils::ArgumentListToString(default_program.runtimeMimeTypes())).toString();
    bool runnable = m_Settings->value("Programs/" + id + "/Runnable", default_program.runnable()).toBool();

    ExternalProgram program;
    program.setExecutablePath(executable);
    program.setArguments(utils::stringToArgumentList(argumentString));
    program.setRuntimeMimeTypes(utils::stringToArgumentList(mimetypeString));
    program.setRunnable(runnable);

    return program;
}

void GlobalSettings::removeExternalProgram(const QString &id)
{
    if(!id.isEmpty())
        m_Settings->remove("Programs/" + id);
}

void GlobalSettings::setExternalProgram(const ExternalProgram &program)
{
    if(!program.isEmpty())
    {
        m_Settings->setValue("Programs/" + program.id() + "/Executable", program.executablePath());
        m_Settings->setValue("Programs/" + program.id() + "/ArgumentString", program.arguments().join("<<"));
        m_Settings->setValue("Programs/" + program.id() + "/MimeTypeString", program.runtimeMimeTypes().join(";"));
        m_Settings->setValue("Programs/" + program.id() + "/Runnable", program.runnable());
    }
}

QList<ExternalProgram> GlobalSettings::getExternalPrograms()
{
    m_Settings->beginGroup("Programs");
    m_Settings->endGroup();
}

