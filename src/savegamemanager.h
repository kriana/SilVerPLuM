#ifndef SAVEGAMEMANAGER_H
#define SAVEGAMEMANAGER_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include "backupsavegame.h"

class Profile;

class SavegameManager : public QObject
{
    Q_OBJECT
public:
    explicit SavegameManager( Profile * p, QObject *parent = 0);

    ~SavegameManager();

    /**
     * @brief Profile of this savegame manager
     * @return
     */
    Profile *profile() const;

    /**
     * @brief Looks for all available savegame ids in backups and profile savegames
     * @return
     */
    QStringList lookForSavegameIds() const;

    /**
     * @brief Gets the savegames in this manager
     * @return
     */
    QMap<QString, BackupSavegame*> getSavegames() const;

    /**
     * @brief Gets all backup savegame IDs (not UIDs!)
     * @return
     */
    QList<QString> getSavegameIds() const;

    /**
     * @brief Gets all savegame UIDs (not backup savegame IDs!)
     * @return
     */
    QSet<QString> getSavegameUIDs();

    /**
     * @brief Gets a backup-savegame with ID (not UID!)
     * @param id
     * @return
     */
    BackupSavegame *getSavegame(const QString & id);

    /**
     * @brief Initializes this manager
     */
    void initialize();

    /**
     * @brief Imports a savegame (not backup-savegame)
     * @param path
     * @return
     */
    bool import(const QString & path);

private:

    Profile * m_profile;

    QMap<QString, BackupSavegame*> m_savegames;

signals:

    void updatedSavegames();

public slots:

    void reloadSavegames();

};

#endif // SAVEGAMEMANAGER_H
