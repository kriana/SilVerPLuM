#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QSettings>
#include <QWidget>
#include <QMainWindow>


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

    /**
     * @brief Returns the path to MSBuild/xbuild
     * @return
     */
    QString getProgramMSBUILD();

    /**
     * @brief Sets the path of MSBuild/xbuild
     * @param program
     */
    void setProgramMSBUILD(const QString & program);

    /**
     * @brief Gets the path of Nuget
     * @return
     */
    QString getProgramNuget();

    /**
     * @brief Sets the path of Nuget
     * @param program
     */
    void setProgramNuget(const QString & program);

private:

    static GlobalSettings * m_pInstance;

    GlobalSettings();

    QSettings * m_Settings;
};

#endif // GLOBALSETTINGS_H
