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
        getLogger().log(Logger::ERROR, "backup-savegame", "restore", "restore", "Prevented restore of " + sav->directory().absolutePath() + ": not a backup!");
        return false;
    }

    QDir destination = m_savegameManager->profile()->profileSavegameDir().absoluteFilePath(id());

    if(destination.exists())
    {
        getLogger().log(Logger::ERROR, "backup-savegame", "restore", "delete-existing", "Deleting existing folder");
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
        getLogger().log(Logger::ERROR, "backup-savegame", "single", "single", "Prevented singe-out of " + sav->directory().absolutePath() + ": not in this entry!");
        return false;
    }

    QString new_id = findNewIdFor(this, m_savegameManager->getSavegameIds());

    getLogger().log(Logger::INFO, "backup-savegame", "single", "single", "Savegame in " + sav->directory().absolutePath() + " will be singled out into id " + new_id);
    QDir destination = m_savegameManager->profile()->profileSavegameDir().absoluteFilePath(new_id);

    if(destination.exists())
    {
        getLogger().log(Logger::INFO, "backup-savegame", "single", "test-existing", "Directory " + destination.absolutePath() + " exists, but seems to be non-functional. Deleting it.");
        destination.removeRecursively();
    }

    utils::copyDirectory(sav->directory(), destination, true);

    // Fix the files or we will break the savegames if renamed
    renameSavegame(destination, id(), new_id);

    m_savegameManager->reloadSavegames();

    return true;
}

bool BackupSavegame::deleteSavegame(Savegame *sav)
{
    if(sav != m_mainSavegame && ! m_BackupSavegames.contains(sav))
    {
        getLogger().log(Logger::ERROR, "backup-savegame", "delete", "delete", "Prevented deletion of " + sav->directory().absolutePath() + ": not in this entry!");
        return false;
    }

    getLogger().log(Logger::INFO, "backup-savegame", "delete", "delete-dir", "Removing " + sav->directory().absolutePath());

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

    return true;
}

bool BackupSavegame::deleteAll()
{
    getLogger().log(Logger::INFO, "backup-savegame", "delete-all", "delete-all", "Begin to delete whole savegame " + id());

    if(m_mainSavegame != nullptr)
    {
        getLogger().log(Logger::INFO, "backup-savegame", "delete-all", "delete-dir", "Removing " + m_mainSavegame->directory().absolutePath());
        m_mainSavegame->directory().removeRecursively();
    }

    for(Savegame * sav : m_BackupSavegames)
    {
        getLogger().log(Logger::INFO, "backup-savegame", "delete-all", "delete-dir", "Removing " + sav->directory().absolutePath());
        sav->directory().removeRecursively();
    }

    getLogger().log(Logger::INFO, "backup-savegame", "delete-all", "delete-all", "Ended process. Triggering reload.");
    m_savegameManager->reloadSavegames();

    return true;
}

bool BackupSavegame::backup()
{
    if(m_mainSavegame != nullptr)
    {
        getLogger().log(Logger::INFO, "backup-savegame", "backup", "backup", "Begin to backup savegame " + id());

        QString bid = QDateTime::currentDateTime().toString("dd-MM-yyyy-HH-mm-ss");
        getLogger().log(Logger::INFO, "backup-savegame", "backup", "backup", "Backup id is " + bid);

        QDir destination = backupDir().absoluteFilePath(bid);

        getLogger().log(Logger::INFO, "backup-savegame", "backup", bid, "Backup directory is " + destination.absolutePath());

        if(destination.exists())
        {
            getLogger().log(Logger::ERROR, "backup-savegame", "backup", bid, "Backup directory already exists! Cancelling!");
            return false;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        destination.mkpath(".");
        utils::copyDirectoryProgress(getMainSavegame()->directory(), destination, true);

        QApplication::restoreOverrideCursor();

        getLogger().log(Logger::INFO, "backup-savegame", "backup", bid, "Loading backup into interface");

        Savegame * sav = Savegame::loadFromDirectory(destination, savegameManager()->profile());


        if(sav == nullptr)
        {
            getLogger().log(Logger::ERROR, "backup-savegame", "backup", bid, "Loading failed!");
        }
        else
        {
            sav->setBackupDate(QDateTime::currentDateTime());
            m_BackupSavegames << sav;
        }

        getLogger().log(Logger::INFO, "backup-savegame", "backup", bid, "Finished backup savegame " + id());

        emit backupListChanged();

        return true;
    }

    return false;
}

bool BackupSavegame::copyTo(Profile *p, QString as)
{
    getLogger().log(Logger::INFO, "backup-savegame", "clone", "clone", "Starting to clone savegame " + id() + " into profile " + p->id());

    if(as.isEmpty())
    {
        as = id();
    }
    else
    {
        getLogger().log(Logger::INFO, "backup-savegame", "clone", "clone", "Will be renamed to " + as);
    }

    if(p->getSavegameManager()->getSavegameIds().contains(as))
    {
        return false;
    }

    QDir destination_savegame = p->profileSavegameDir().absoluteFilePath(as);
    QDir destination_backupsavegame = p->profileSavegameBackupDir().absoluteFilePath(as);

    if(destination_savegame.exists())
    {
        getLogger().log(Logger::WARNING, "backup-savegame", "clone", "test-existing", "Deleting non-functional savegame dir");
        destination_savegame.removeRecursively();
    }
    if(destination_backupsavegame.exists())
    {
        getLogger().log(Logger::WARNING, "backup-savegame", "clone", "test-existing", "Deleting non-functional savegame backup dir");
        destination_backupsavegame.removeRecursively();
    }

    if(m_mainSavegame != nullptr)
    {
        getLogger().log(Logger::INFO, "backup-savegame", "clone", "copy", "Copy savegame ...");
        utils::copyDirectory(m_mainSavegame->directory(), destination_savegame, true);
        renameSavegame(destination_savegame, id(), as);
    }

    getLogger().log(Logger::INFO, "backup-savegame", "clone", "copy", "Copy savegame backups ...");
    utils::copyDirectory(backupDir(), destination_backupsavegame, true);

    for(QString bid : destination_backupsavegame.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        renameSavegame(destination_backupsavegame.absoluteFilePath(bid), id(), as);
    }

    p->getSavegameManager()->reloadSavegames();

    getLogger().log(Logger::INFO, "backup-savegame", "clone", "clone", "Operation finished.");

    return true;
}

bool BackupSavegame::backupUseful()
{
    if(m_mainSavegame != nullptr)
    {
        for(Savegame * sav : m_BackupSavegames)
        {
            if(sav->contentEquals(sav))
            {
                return false;
            }
        }
    }

    return true;
}

void BackupSavegame::pruneBackups()
{
    getLogger().log(Logger::INFO, "backup-savegame", "prune", "prune", "Starting to prune backups");

    QSet<Savegame*> todelete;
    QList<Savegame*> backups = getBackupSavegames();

    for(int i = 0; i < backups.size(); ++i)
    {
        Savegame * here = backups[i];

        if(!todelete.contains(here))
        {
            if(m_mainSavegame != nullptr && here->contentEquals(m_mainSavegame))
            {
                getLogger().log(Logger::INFO, "backup-savegame", "prune", "find", here->directory().absolutePath() + " is equal to current savegame. Will be deleted.");
                todelete << here;
                continue;
            }

            for(int j = i + 1; j < backups.size(); ++j)
            {
                Savegame * there = backups[j];

                if(there->contentEquals(here))
                {
                    getLogger().log(Logger::INFO, "backup-savegame", "prune", "find", there->directory().absolutePath() + " is equal to " + here->directory().absolutePath() +  ". Will be deleted.");
                    todelete << there;
                }
            }
        }
    }

    for(Savegame * sav : todelete)
    {
        deleteSavegame(sav);
    }

    getLogger().log(Logger::INFO, "backup-savegame", "prune", "prune", "Pruning finished");
}

QString BackupSavegame::findNewIdFor(BackupSavegame *sav, const QStringList &ids)
{
    QString prefix;

    // If somebody tinkered with the folder names, use a different naming schema
    if(sav->id().contains("_"))
    {
        prefix = sav->id().split("_").first();
    }
    else
    {
        prefix = "save";
    }

    // Use STL random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);

    QString new_id;

    while(new_id.isEmpty() || ids.contains(new_id))
    {
        new_id = prefix + "_" + QString::number(dis(gen));
    }

    return new_id;
}

void BackupSavegame::renameSavegame(QDir dir, const QString &old_id, const QString &new_id)
{
    if(old_id != new_id)
    {
        dir.rename(old_id, new_id);
        dir.rename(old_id + "_old", new_id + "_old");
    }
}

void BackupSavegame::initialize()
{
    getLogger().log(Logger::INFO, "backup-savegame", "init", "load", "Begin to load savegame with id " + id());

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

    getLogger().log(Logger::INFO, "backup-savegame", "init", "load", "Ended loading savegame");
}
