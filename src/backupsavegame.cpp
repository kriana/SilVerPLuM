#include "backupsavegame.h"
#include "savegamemanager.h"
#include "profile.h"
#include <QApplication>
#include "utils.h"
#include <QMessageBox>
#include <random>

BackupSavegame::BackupSavegame(const QString & id, SavegameManager * mgr) :m_id(id), m_savegameManager(mgr)
{
    initialize();
}

BackupSavegame::~BackupSavegame()
{
    if(m_mainSavegame != nullptr)
        delete m_mainSavegame;

    for(Savegame * sav : m_BackupSavegames)
    {
        delete sav;
    }
}

SavegameManager * BackupSavegame::savegameManager() const
{
    return m_savegameManager;
}

QString BackupSavegame::id() const
{
    return m_id;
}

Logger & BackupSavegame::getLogger()
{
    return savegameManager()->profile()->getLogger();
}

Savegame *BackupSavegame::getMainSavegame() const
{
    return m_mainSavegame;
}

QList<Savegame *> BackupSavegame::getBackupSavegames() const
{
    QList<Savegame *> result(m_BackupSavegames);
    std::sort(result.begin(), result.end(), [](Savegame * a, Savegame * b) {
       return a->backupDate() > b->backupDate();
    });

    return result;
}

Savegame *BackupSavegame::getAnySavegame() const
{
    if(m_mainSavegame != nullptr)
        return m_mainSavegame;

    for(Savegame * sav : getBackupSavegames())
    {
        return sav;
    }

    return nullptr;
}

bool BackupSavegame::isEmpty() const
{
    return m_mainSavegame == nullptr && m_BackupSavegames.isEmpty();
}

QDir BackupSavegame::backupDir() const
{
    return m_savegameManager->profile()->profileSavegameBackupDir().absoluteFilePath(id());
}

bool BackupSavegame::restore(Savegame *sav)
{
    if(!m_BackupSavegames.contains(sav))
    {
        getLogger().log(Logger::Error, "backup-savegame", "restore", "restore", "Prevented restore of " + sav->directory().absolutePath() + ": not a backup!");
        return false;
    }

    QDir destination = m_savegameManager->profile()->profileSavegameDir().absoluteFilePath(id());

    if(destination.exists())
    {
        getLogger().log(Logger::Error, "backup-savegame", "restore", "delete-existing", "Deleting existing folder");
        destination.removeRecursively();
    }

    utils::copyDirectory(sav->directory(), destination, true);

    m_savegameManager->reloadSavegames();
    return true;
}

bool BackupSavegame::single(Savegame *sav)
{
    if(sav != m_mainSavegame && ! m_BackupSavegames.contains(sav))
    {
        getLogger().log(Logger::Error, "backup-savegame", "single", "single", "Prevented singe-out of " + sav->directory().absolutePath() + ": not in this entry!");
        return false;
    }

    sav->copyTo(savegameManager()->profile()->profileSavegameDir(), false);
    m_savegameManager->reloadSavegames();

    return true;
}

bool BackupSavegame::deleteSavegame(Savegame *sav)
{
    if(sav != m_mainSavegame && ! m_BackupSavegames.contains(sav))
    {
        getLogger().log(Logger::Error, "backup-savegame", "delete", "delete", "Prevented deletion of " + sav->directory().absolutePath() + ": not in this entry!");
        return false;
    }

    getLogger().log(Logger::Info, "backup-savegame", "delete", "delete-dir", "Removing " + sav->directory().absolutePath());

    sav->directory().removeRecursively();

    if(sav == m_mainSavegame)
    {
        delete m_mainSavegame;
        m_mainSavegame = nullptr;

        emit mainSavegameChanged();
    }
    else
    {
        m_BackupSavegames.removeAll(sav);
        delete sav;

        emit backupListChanged();
    }

    if(getAnySavegame() == nullptr)
    {
        m_savegameManager->reloadSavegames();
    }

    return true;
}

bool BackupSavegame::deleteAll()
{
    getLogger().log(Logger::Info, "backup-savegame", "delete-all", "delete-all", "Begin to delete whole savegame " + id());

    if(m_mainSavegame != nullptr)
    {
        getLogger().log(Logger::Info, "backup-savegame", "delete-all", "delete-dir", "Removing " + m_mainSavegame->directory().absolutePath());
        m_mainSavegame->directory().removeRecursively();
    }

    for(Savegame * sav : m_BackupSavegames)
    {
        getLogger().log(Logger::Info, "backup-savegame", "delete-all", "delete-dir", "Removing " + sav->directory().absolutePath());
        sav->directory().removeRecursively();
    }

    getLogger().log(Logger::Info, "backup-savegame", "delete-all", "delete-all", "Ended process. Triggering reload.");
    m_savegameManager->reloadSavegames();

    return true;
}

bool BackupSavegame::backup()
{
    if(m_mainSavegame != nullptr)
    {
        getLogger().log(Logger::Info, "backup-savegame", "backup", "backup", "Begin to backup savegame " + id());

        QString bid = QDateTime::currentDateTime().toString("dd-MM-yyyy-HH-mm-ss");
        getLogger().log(Logger::Info, "backup-savegame", "backup", "backup", "Backup id is " + bid);

        QDir destination = backupDir().absoluteFilePath(bid);

        getLogger().log(Logger::Info, "backup-savegame", "backup", bid, "Backup directory is " + destination.absolutePath());

        if(destination.exists())
        {
            getLogger().log(Logger::Error, "backup-savegame", "backup", bid, "Backup directory already exists! Cancelling!");
            return false;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        destination.mkpath(".");
        utils::copyDirectoryProgress(getMainSavegame()->directory(), destination, true);

        QApplication::restoreOverrideCursor();

        getLogger().log(Logger::Info, "backup-savegame", "backup", bid, "Loading backup into interface");

        Savegame * sav = Savegame::loadFromDirectory(destination, savegameManager()->profile());


        if(sav == nullptr)
        {
            getLogger().log(Logger::Error, "backup-savegame", "backup", bid, "Loading failed!");
        }
        else
        {
            sav->setBackupDate(QDateTime::currentDateTime());
            m_BackupSavegames << sav;
        }

        getLogger().log(Logger::Info, "backup-savegame", "backup", bid, "Finished backup savegame " + id());

        emit backupListChanged();

        return true;
    }

    return false;
}

bool BackupSavegame::copyTo(Profile *p, OverwriteBehavior behavior)
{
    getLogger().log(Logger::Info, "backup-savegame", "clone", "clone", "Starting to clone savegame " + id() + " into profile " + p->id());

    QString uid = getAnySavegame()->uid();

    if(p->getSavegameManager()->getSavegameUIDs().contains(uid))
    {
        switch(behavior)
        {
        case DontOverwrite:
            return false;
        case Overwrite:
            break;
        case Rename:
            uid = Savegame::findNewUID(p);
            break;
        }
    }


    QDir destination_savegame = p->profileSavegameDir().absoluteFilePath(getAnySavegame()->generatedDirectoryPrefix() +  "_" + uid);
    QDir destination_backupsavegame = p->profileSavegameBackupDir().absoluteFilePath(getAnySavegame()->generatedDirectoryPrefix() +  "_" + uid);

    if(destination_savegame.exists())
    {
        getLogger().log(Logger::Warning, "backup-savegame", "clone", "test-existing", "Deleting non-functional savegame dir");
        destination_savegame.removeRecursively();
    }
    if(destination_backupsavegame.exists())
    {
        getLogger().log(Logger::Warning, "backup-savegame", "clone", "test-existing", "Deleting non-functional savegame backup dir");
        destination_backupsavegame.removeRecursively();
    }

    if(m_mainSavegame != nullptr)
    {
        getLogger().log(Logger::Info, "backup-savegame", "clone", "copy", "Copy savegame ...");
        m_mainSavegame->copyToAsWithDirName(destination_savegame.absolutePath(), uid);
    }

    getLogger().log(Logger::Info, "backup-savegame", "clone", "copy", "Copy savegame backups ...");
    for(Savegame * sav : m_BackupSavegames)
    {
        QString path = destination_backupsavegame.absoluteFilePath(sav->directory().dirName());
        sav->copyToAsWithDirName(path, uid);
    }

    p->getSavegameManager()->reloadSavegames();

    getLogger().log(Logger::Info, "backup-savegame", "clone", "clone", "Operation finished.");

    return true;
}

bool BackupSavegame::backupUseful()
{
    if(m_mainSavegame != nullptr)
    {
        for(Savegame * sav : m_BackupSavegames)
        {
            if(m_mainSavegame->contentEquals(sav))
            {
                return false;
            }
        }
    }

    return true;
}

void BackupSavegame::pruneBackups()
{
    getLogger().log(Logger::Info, "backup-savegame", "prune", "prune", "Starting to prune backups");

    QSet<Savegame*> todelete;
    QList<Savegame*> backups = getBackupSavegames();

    for(int i = 0; i < backups.size(); ++i)
    {
        Savegame * here = backups[i];

        if(!todelete.contains(here))
        {
            /*if(m_mainSavegame != nullptr && here->contentEquals(m_mainSavegame))
            {
                getLogger().log(Logger::INFO, "backup-savegame", "prune", "find", here->directory().absolutePath() + " is equal to current savegame. Will be deleted.");
                todelete << here;
                continue;
            }*/

            for(int j = i + 1; j < backups.size(); ++j)
            {
                Savegame * there = backups[j];

                if(there->contentEquals(here))
                {
                    getLogger().log(Logger::Info, "backup-savegame", "prune", "find", there->directory().absolutePath() + " is equal to " + here->directory().absolutePath() +  ". Will be deleted.");
                    todelete << there;
                }
            }
        }
    }

    for(Savegame * sav : todelete)
    {
        deleteSavegame(sav);
    }

    getLogger().log(Logger::Info, "backup-savegame", "prune", "prune", "Pruning finished");
}

void BackupSavegame::initialize()
{
    getLogger().log(Logger::Info, "backup-savegame", "init", "load", "Begin to load savegame with id " + id());

    m_mainSavegame = Savegame::loadFromDirectory(savegameManager()->profile()->profileSavegameDir().absoluteFilePath(id()),
                                                 savegameManager()->profile());

    QDir backupdir = savegameManager()->profile()->profileSavegameBackupDir().absoluteFilePath(id());
    backupdir.mkdir("."); // Create if needed

    for(QString bid : backupdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        Savegame * sav = Savegame::loadFromDirectory(backupdir.absoluteFilePath(bid),
                                                     savegameManager()->profile());

        if(sav != nullptr)
        {
            m_BackupSavegames << sav;
        }
    }

    getLogger().log(Logger::Info, "backup-savegame", "init", "load", "Ended loading savegame");
}
