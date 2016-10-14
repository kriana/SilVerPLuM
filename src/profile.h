#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QDir>
#include <QSettings>
#include <QList>
#include <QObject>
#include "launcher.h"
#include "vanillalauncher.h"
#include "modmanager.h"
#include "logger.h"
#include "savegamemanager.h"

class Profile : public QObject
{

    Q_OBJECT

public:

    /**
     * @brief Name of the default profiles
     */
    static QString DEFAULT_PROFILE_NAME;

    /**
     * @brief ID of the default profile
     */
    static QString DEFAULT_PROFILE_ID;

    Profile(const QString & id);

    ~Profile();    

    /**
     * @brief The directory of this profile
     * @return
     */
    QDir profileBaseDir();

    /**
     * @brief Savegame directory of this profile
     * @return
     */
    QDir profileSavegameDir();

    /**
     * @brief Savegame backup directory of this profile
     * @return
     */
    QDir profileSavegameBackupDir();

    /**
     * @brief Modification directory of this profile
     * @return
     */
    QDir profileModDir();

    /**
     * @brief Identifier of this profile
     * @return
     */
    QString id() const;

    /**
     * @brief Sets ID of this profile
     * @param id
     */
    void setId(const QString &id);

    /**
     * @brief Name of this profile
     * @return
     */
    QString name() const;

    /**
     * @brief Sets the name of this profile
     * @param name
     */
    void setName(const QString & name);

    /**
     * @brief Description of this profile in Markdown format
     * @return
     */
    QString description() const;

    /**
     * @brief Sets the description of this profile in Markdown format
     * @param desc
     */
    void setDescription(const QString & desc);

    /**
     * @brief The Stardew Valley dir
     * @return
     */
    QDir StardewValleyDir();

    /**
     * @brief Sets the Stardew Valley dir
     * @param dir
     */
    void setStardewValleyDir(const QDir & dir);

    /**
     * @brief The savegame dir of Stardew Valley
     * @return
     */
    QDir StardewValleySavegameDir();

    /**
     * @brief Sets the savegame dir of Stardew Valley
     * @param dir
     */
    void setStardewValleySavegameDir(const QDir & dir);

    /**
     * @brief The user data dir of Stardew Valley
     * @return
     */
    QDir StardewValleyUserDataDir();

    /**
     * @brief Sets the user data dir of Stardew Valley
     * @param dir
     */
    void setStardewValleyUserDataDir(const QDir & dir);

    /**
     * @brief The current version of Stardew Valley
     * @return
     */
    QVersionNumber StardewValleyVersion();

    /**
     * @brief Sets the current version of Stardew Valley
     * @param version
     */
    void setStardewValleyVersion(const QVersionNumber & version);

    /**
     * @brief Gets the current Technology used by Stardew Valley
     * @return
     */
    Platform::GameTechnology StardewValleyTechnology();

    /**
     * @brief Sets the current technology used by Stardew Valley
     * @param tech
     */
    void setStardewValleyTechnology(Platform::GameTechnology tech);

    /**
     * @brief Returns the stardew valley technology as string
     * @return
     */
    QString StardewValleyTechnologyString();

    /**
     * @brief If enabled, a backup of all savegames is created on start
     * @return
     */
    bool enableBackupOnStart();

    /**
     * @brief Enable/disable if savegames shouldbe backed up before game launch
     * @param enabled
     */
    void setEnableBackupOnStart(bool enabled);

    /**
     * @brief If enabled, backups should be checked if they are useful (only created if something changed)
     * @return
     */
    bool checkForExistingBackups();

    /**
     * @brief Enabled/disables checking for existing backups
     * @param enabled
     */
    void setCheckForExistingBackups(bool enabled);

    /**
     * @brief Backup interval in seconds. 0 if disabled.
     * @return
     */
    int backupInterval();

    /**
     * @brief Sets the backup interval. Set to 0 to disable.
     * @param interval
     */
    void setBackupInterval(int interval);

    /**
     * @brief Returns true if the profile directory exists
     * @return
     */
    bool exists();

    /**
     * @brief Sets the current launcher
     * @param id
     */
    void setLauncher(const QString & id);

    /**
     * @brief Gets the current launcher
     * @return
     */
    Launcher * getLauncher();

    /**
     * @brief Get launcher with ID
     * @param id
     * @return
     */
    Launcher * getLauncher(const QString & id);

    /**
     * @brief Get the list of all launchers
     * @return
     */
    QList<Launcher*> getLaunchers();

    /**
     * @brief Initialize this profile
     */
    void initialize();

    /**
     * @brief Fixes some crazy things that are annoying AF
     */
    void fixCrazyness();

public slots:

    /**
     * @brief Creates the directories of this profile
     */
    void repairDirectories();

private:

    QString m_Id;

    QSettings * m_Settings;

    QList<Launcher *> m_Launchers;

    ModManager * m_modManager;

    SavegameManager * m_savegameManager;

    Logger m_logger;

    bool m_updateBatch;

    void setting_changed();

signals:

    void updated();

    void updatedSettings();

    void updatedMods();

    void updatedSavegames();

public:

    /**
     * @brief Platform-specific technology
     * @return
     */
    static Platform::GameTechnology DefaultStardewValleyTechnology();

    /**
     * @brief Platform-specific locations for Stardew Valley savegames
     * @return
     */
    static QDir DefaultStardewValleySavegameDir();

    /**
     * @brief Platform-specific locations for Stardew Valley userdata (savegames are a subfolder)
     * @return
     */
    static QDir DefaultStardewValleyUserDataDir();

    /**
     * @brief Platform-specific locations for Stardew Valley
     * @return
     */
    static QDir DefaultStardewValleyDir();

    /**
     * @brief Returns known Stardew Valley versions
     * @return
     */
    static QStringList StardewValleyVersions();

    ModManager *getModManager() const;

    Logger & getLogger();

    SavegameManager *getSavegameManager() const;

    bool getUpdateBatch() const;

    /**
     * @brief Set to true to disable update() event for batched storage. If set to false, the actions will be executed.
     * @param updateBatch
     */
    void setUpdateBatch(bool updateBatch);
};

#endif // PROFILE_H
