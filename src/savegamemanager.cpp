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

void SavegameManager::import(const QString &path)
{
    profile()->getLogger().log(Logger::INFO, "savegames", "manager", "import", "Importing savegame in " + path);

    QTemporaryDir tmp;

    if(tmp.isValid())
    {
        JlCompress::extractDir(path, tmp.path());

        // Determine the identifier
        QString id;

        for(QString & file : QDir(tmp.path()).entryList(QDir::Files))
        {
            if(file.contains("_") && !file.contains(".") && !file.endsWith("_old"))
            {
                id = file;
            }
        }

        profile()->getLogger().log(Logger::INFO, "savegames", "manager", "import", "ID is " + id);

        Savegame * sav = Savegame::loadFromDirectory(tmp.path(), profile());

        if(sav == nullptr)
        {
            profile()->getLogger().log(Logger::ERROR, "savegames", "manager", "import", "Not able to load savegame. Cancelling.");
            throw std::runtime_error("Unable to load savegame");
        }

        delete sav;

        if(getSavegameIds().contains(id))
        {
            profile()->getLogger().log(Logger::INFO, "savegames", "manager", "import", "ID already exists. Renaming.");
            QString new_id = Savegame::findNewIdFor(id, getSavegameIds());
            BackupSavegame::renameSavegame(tmp.path(), id, new_id);

            id = new_id;
        }

        profile()->getLogger().log(Logger::INFO, "savegames", "manager", "import", "Copying ...");
        QDir destination = profile()->profileSavegameDir().absoluteFilePath(id);
        destination.removeRecursively();

        utils::copyDirectory(tmp.path(), destination, true);

        profile()->getLogger().log(Logger::INFO, "savegames", "manager", "import", "Finished");

        reloadSavegames();

    }
    else
    {
        profile()->getLogger().log(Logger::ERROR, "savegames", "manager", "import", "Unable to create temp. dir");
        throw std::runtime_error("Cannot create temp dir");
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

    emit reloaded();
}
