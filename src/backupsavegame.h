#ifndef BACKUPSAVEGAME_H
#define BACKUPSAVEGAME_H

#include <QString>
#include "savegame.h"
#include <QObject>

class SavegameManager;

/**
 * @brief Manages a savegame ID with its current backups
 */
class BackupSavegame : public QObject
{
    Q_OBJECT

public:

    enum OverwriteBehavior
    {
        DontOverwrite,
        Overwrite,
        Rename
    };

    BackupSavegame(const QString &id, SavegameManager *mgr);

    ~BackupSavegame();

    SavegameManager *savegameManager() const;

    /**
     * @brief The ID of this backup-savegame. Usually FarmerName_UID
     * @return
     */
    QString id() const;

    /**
     * @brief Gets the logger for this object
     * @return
     */
    Logger &getLogger();

    /**
     * @brief Gets the currently active savegame. Can be nullptr.
     * @return
     */
    Savegame *getMainSavegame() const;

    /**
     * @brief Gets a list of backup savegames sorted by date.
     * @return
     */
    QList<Savegame *> getBackupSavegames() const;

    /**
     * @brief Gets the main savegame or the newest backup savegame. Can be nullptr.
     * @return
     */
    Savegame *getAnySavegame() const;

    /**
     * @brief Returns true if there's no savegame in this backup savegame.
     * @return
     */
    bool isEmpty() const;

    /**
     * @brief The directory used for the backups
     * @return
     */
    QDir backupDir() const;

    /**
     * @brief Restores a backup
     * @param sav
     * @return
     */
    bool restore(Savegame * sav);

    /**
     * @brief Creates a completely new savegame from one specific savegame
     * @param sav
     * @return
     */
    bool single(Savegame * sav);

    /**
     * @brief Deletes main or backup savegame
     * @param sav
     * @return
     */
    bool deleteSavegame(Savegame * sav);

    /**
     * @brief Deletes this entry completely
     * @return
     */
    bool deleteAll();

    /**
     * @brief Backup the main savegame
     * @return
     */
    bool backup();

    /**
     * @brief Copy this entry to another profile
     * @param p
     * @return
     */
    bool copyTo(Profile * p, OverwriteBehavior behavior);


    /**
     * @brief Returns true if the savegame actually changed and a backup is useful
     * @return
     */
    bool backupUseful();


    /**
     * @brief Removes all backups that have duplicates
     */
    void pruneBackups();

private:

    QString m_id;

    SavegameManager * m_savegameManager;

    Savegame * m_mainSavegame = nullptr;

    QList<Savegame *> m_BackupSavegames;

    void initialize();

signals:

    void mainSavegameChanged();

    void backupListChanged();
};

#endif // BACKUPSAVEGAME_H
