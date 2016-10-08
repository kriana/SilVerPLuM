#include "savegamemanager.h"
#include "profile.h"

SavegameManager::SavegameManager(Profile *p, QObject *parent) : QObject(parent), m_profile(p)
{

}

SavegameManager::~SavegameManager()
{

}

Profile *SavegameManager::profile() const
{
    return m_profile;
}

QStringList SavegameManager::lookForSavegameIds() const
{
    QSet<QString> ids;

    for(QString id : profile()->profileSavegameDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        ids.insert(id);
    }

    for(QString id : profile()->profileSavegameBackupDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        ids.insert(id);
    }

    return ids.toList();
}

QMap<QString, BackupSavegame *> SavegameManager::getSavegames() const
{
    return QMap<QString, BackupSavegame*>(m_savegames);
}

QList<QString> SavegameManager::getSavegameIds() const
{
    return m_savegames.keys();
}

BackupSavegame * SavegameManager::getSavegame(const QString &id)
{
    return m_savegames[id];
}

void SavegameManager::initialize()
{
    reloadSavegames();
}

void SavegameManager::reloadSavegames()
{
    for(BackupSavegame * sav : m_savegames.values())
    {
        sav->deleteLater();
    }
    m_savegames.clear();

    for(QString id : lookForSavegameIds())
    {
        BackupSavegame * sav = new BackupSavegame(id, this);
        if(!sav->isEmpty())
            m_savegames[id] = sav;
        else
            delete sav;
    }

    emit reloaded();
}
