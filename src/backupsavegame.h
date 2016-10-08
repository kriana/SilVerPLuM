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
    BackupSavegame(const QString &id, SavegameManager *mgr);

    ~BackupSavegame();

    SavegameManager *savegameManager() const;

    QString id() const;

    Logger &getLogger();

    Savegame *getMainSavegame() const;

    QList<Savegame *> getBackupSavegames() const;

    bool isEmpty() const;

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
    bool copyTo(Profile * p, QString as = "");

    /**
     * @brief Finds a new valid ID
     * @param sav
     * @return
     */
    static QString findNewIdFor(BackupSavegame *sav, const QStringList & ids );

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
