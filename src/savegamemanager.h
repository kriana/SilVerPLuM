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

    Profile *profile() const;

    /**
     * @brief Looks for all available savegame ids in backups and profile savegames
     * @return
     */
    QStringList lookForSavegameIds() const;

    QMap<QString, BackupSavegame*> getSavegames() const;

    QList<QString> getSavegameIds() const;

    BackupSavegame *getSavegame(const QString & id);

    void initialize();

    void import(const QString & path);

private:

    Profile * m_profile;

    QMap<QString, BackupSavegame*> m_savegames;

signals:

    void updatedSavegames();

public slots:

    void reloadSavegames();

};

#endif // SAVEGAMEMANAGER_H
