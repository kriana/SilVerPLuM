#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QSettings>
#include <QWidget>
#include <QMainWindow>
#include "externalprogram.h"
#include <QMap>

class GlobalSettings
{
public:

    ~GlobalSettings();

    static GlobalSettings * instance();

    /**
     * @brief Sets the window state of the application
     * @param widget
     */
    void setWindowState(QMainWindow * widget);

    /**
     * @brief Restores the window state of the application
     * @param widget
     */
    void getWindowState(QMainWindow *widget);

    /**
     * @brief Returns the currently selected profile
     * @return
     */
    QString getCurrentProfile();

    /**
     * @brief Sets the currently select profile
     * @param profileid
     */
    void setCurrentProfile(const QString & profileid);

    /**
     * @brief Returns true if DLL-compile mods should switch to the user's technology settings
     * @return
     */
    bool getDLLRedirectXNA();

    /**
     * @brief Enables/disables the switch between XNA and MonoGame for DLL-compile mods
     * @param enabled
     */
    void setDLLRedirectXNA(bool enabled);

    /**
     * @brief If true, pipelines should avoid re-priming
     * @return
     */
    bool getEnablePrimeCache();

    /**
     * @brief Enable/disable if pipelines should avoid re-priming
     * @param enabled
     */
    void setEnablePrimeCache(bool enabled);

    /**
     * @brief If true, the user can enable unsupported pipelines
     * @return
     */
    bool getForceUnsupported();

    /**
     * @brief Enable/disable if the user can enable unsupported pipelines
     * @param enabled
     */
    void setForceUnsupported(bool enabled);

    /**
     * @brief If true, the application should avoid writing outside the desired directories and their children and as well prevent overwriting existing game files
     * @return
     */
    bool getEnableFileGuard();

    /**
     * @brief Enable/disable protection of files
     * @param enabled
     */
    void setEnableFileGuard(bool enabled);

    /**
     * @brief If true, the application should check dependencies
     * @return
     */
    bool getEnableDepencencyCheck();

    /**
     * @brief Enable/disable dependency-checking
     * @param enabled
     */
    void setEnableDependencyCheck(bool enabled);

    /**
     * @brief If true, the dependency-check should look for the right order of mods
     * @return
     */
    bool getEnableDepencyCheckPriorityAwareness();

    /**
     * @brief Enable/disable looking for the right order while dependency-checking
     * @param enabled
     */
    void setEnableDepencyCheckPriorityAwareness(bool enabled);

    /**
     * @brief If true, the launcher should backup savegames into temporary directories before copying from the profile
     * @return
     */
    bool getRunningBackupSDVSavegames();

    /**
     * @brief Enable/disable backup before clearing the game's savegame dir
     * @param enabled
     */
    void setRunningBackupSDVSavegames(bool enabled);

    /**
     * @brief If true, the launcher should create a backup of the profile's savegames before copying the savegames after launch
     * @return
     */
    bool getRunningBackupProfileSavegames();

    /**
     * @brief Enable/disable backup of profile savegames before moving post-launch savegames
     * @param enabled
     */
    void setRunningBackupProfileSavegames(bool enabled);

    ExternalProgram getExternalProgram(const QString & id);

    void removeExternalProgram(const QString & id);

    void setExternalProgram(const QString &id, const ExternalProgram & program);

    QList<ExternalProgram> getExternalPrograms();

    QStringList getExternalProgramIds();

private:

    static GlobalSettings * m_pInstance;

    GlobalSettings();

    QSettings * m_Settings;

    QMap<QString, ExternalProgram> m_DefaultExternalPrograms;

    void initializeDefaultExternalPrograms();

    void initializeWindowsExternalPrograms();

    void initializeLinuxExternalPrograms();

    void initializeMacExternalPrograms();
};

#endif // GLOBALSETTINGS_H
