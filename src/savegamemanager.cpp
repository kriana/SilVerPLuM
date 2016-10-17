#include "savegamemanager.h"
#include "profile.h"
#include <JlCompress.h>
#include "utils.h"

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
        if(id.contains("_"))
            ids.insert(id);
    }

    for(QString id : profile()->profileSavegameBackupDir().entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        if(id.contains("_"))
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

QSet<QString> SavegameManager::getSavegameUIDs()
{
    QSet<QString> existing_uids;

    for(BackupSavegame * sav : profile()->getSavegameManager()->getSavegames().values())
    {
        existing_uids << sav->getAnySavegame()->uid();
    }

    return existing_uids;
}

BackupSavegame * SavegameManager::getSavegame(const QString &id)
{
    return m_savegames[id];
}

void SavegameManager::initialize()
{
    reloadSavegames();
}

bool SavegameManager::import(const QString &path)
{
    profile()->getLogger().log(Logger::Info, "savegames", "manager", "import", "Importing savegame in " + path);

    QTemporaryDir tmp;

    if(tmp.isValid())
    {
        JlCompress::extractDir(path, tmp.path());     

        Savegame * sav = Savegame::loadFromDirectory(tmp.path(), profile());

        if(sav == nullptr)
        {
            profile()->getLogger().log(Logger::Error, "savegames", "manager", "import", "Not able to load savegame. Cancelling.");
            return false;
        }

        sav->copyTo(profile()->profileSavegameDir(), false);

        delete sav;

        profile()->getLogger().log(Logger::Info, "savegames", "manager", "import", "Finished");

        reloadSavegames();

        return true;

    }
    else
    {
        profile()->getLogger().log(Logger::Error, "savegames", "manager", "import", "Unable to create temp. dir");
        return false;
    }
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

    emit updatedSavegames();
}
