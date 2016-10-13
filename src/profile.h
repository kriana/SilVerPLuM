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

    static QString DEFAULT_PROFILE_NAME;
    static QString DEFAULT_PROFILE_ID;

    Profile(const QString & id);

    ~Profile();    

    QDir profileBaseDir();

    QDir profileSavegameDir();

    QDir profileSavegameBackupDir();

    QDir profileModDir();

    QString id() const;

    void setId(const QString &id);

    QString name() const;

    void setName(const QString & name);

    QString description() const;

    void setDescription(const QString & desc);

    QDir StardewValleyDir();

    void setStardewValleyDir(const QDir & dir);

    QDir StardewValleySavegameDir();

    void setStardewValleySavegameDir(const QDir & dir);

    QDir StardewValleyUserDataDir();

    void setStardewValleyUserDataDir(const QDir & dir);

    QVersionNumber StardewValleyVersion();

    void setStardewValleyVersion(const QVersionNumber & version);

    Platform::GameTechnology StardewValleyTechnology();

    void setStardewValleyTechnology(Platform::GameTechnology tech);

    QString StardewValleyTechnologyString();

    /**
     * @brief If enabled, a backup of all savegames is created on start
     * @return
     */
    bool enableBackupOnStart();

    void setEnableBackupOnStart(bool enabled);

    /**
     * @brief If enabled, backups should be checked if they are useful (only created if something changed)
     * @return
     */
    bool checkForExistingBackups();

    void setCheckForExistingBackups(bool enabled);

    /**
     * @brief Backup interval in seconds. 0 if disabled.
     * @return
     */
    int backupInterval();

    void setBackupInterval(int interval);

    bool exists();

    void setLauncher(const QString & id);

    Launcher * getLauncher();

    Launcher * getLauncher(const QString & id);

    QList<Launcher*> getLaunchers();

    void initialize();

    /**
     * @brief Fixes some crazy things that are annoying AF
     */
    void fixCrazyness();

public slots:

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
