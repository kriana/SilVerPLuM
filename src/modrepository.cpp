#include "modrepository.h"
#include "modmanager.h"
#include <QRegExp>
#include <QMap>
#include <QTemporaryFile>

ModRepository::ModRepository(ModManager *mgr) : QObject(mgr), m_modManager(mgr)
{
    triggerNeedsUpdate();

    m_downloadManager = new DownloadManager(this);
    m_downloadManager->setLogger(&(getLogger()));

    connect(mgr, SIGNAL(updatedModList()), this, SLOT(triggerNeedsUpdate()));
    connect(mgr, SIGNAL(updatedModList()), this, SLOT(triggerLookForUpdates()));
    connect(mgr, SIGNAL(updatedModStatus(QString,QString,bool)), this, SLOT(triggerNeedsUpdate()));

    connect(m_downloadManager, SIGNAL(finished()), this, SLOT(downloadsFinished()));
    connect(m_downloadManager, SIGNAL(progress(int, int, int)), this, SIGNAL(downloadProgress(int, int, int)));
}

ModRepository::~ModRepository()
{
    clear();
}

bool ModRepository::needsUpdate() const
{
    return m_needsUpdate;
}

void ModRepository::triggerNeedsUpdate()
{
    m_needsUpdate = true;
    emit repositoryNeedsUpdate();
}

void ModRepository::triggerLookForUpdates()
{
    lookForUpdates();
    emit repositoryUpdated(true);
}

ModManager *ModRepository::getModManager() const
{
    return m_modManager;
}

void ModRepository::install(QList<ModRepositoryEntry *> entries, bool update)
{
    if(m_status != RepositoryIdle)
        return;

    QList<DownloadManager::DownloadItem> downloads;

    for(ModRepositoryEntry * entry : entries)
    {
        QString filename;

        {
            QTemporaryFile dst;
            if(dst.open())
            {
                filename = dst.fileName() + ".zip";
                dst.close();
            }
        }

        if(filename.isEmpty())
        {
            getLogger().log(Logger::Error, "modrepository", "download-mod", "prepare", "Cannot create temporary file for writing!");
            continue;
        }

        DownloadManager::DownloadItem item(entry->modDownloadURL(), filename);

        item.purpose = update ? DownloadPurposeModDownloadUpdate : DownloadPurposeModDownloadInstall;
        downloads << item;
    }

    // Start downloads
    if(!downloads.isEmpty())
    {
        setStatus(RepositoryDownloadingMod);
        m_downloadManager->append(downloads);
    }
}

QList<ModRepositoryEntry *> ModRepository::getEntries() const
{
    return m_entries;
}

QList<ModRepositoryEntry *> ModRepository::getUpdates() const
{
    return m_updates;
}

QString ModRepository::getModTempDir() const
{
    return m_modTempDir.path();
}

void ModRepository::cancelCurrentAction()
{
    switch(m_status)
    {
    case RepositoryDownloadingRepositories:
        setStatus(RepositoryIdle);
        m_downloadManager->cancelDownloads();
        break;
    case RepositoryDownloadingData:
        setStatus(RepositoryIdle);
        m_downloadManager->cancelDownloads();
        break;
    case RepositoryDownloadingMod:
        setStatus(RepositoryIdle);
        m_downloadManager->cancelDownloads();
        break;
    default:
        break;
    }
}

ModRepository::RepositoryStatus ModRepository::getStatus() const
{
    return m_status;
}

Logger &ModRepository::getLogger()
{
    return m_modManager->getLogger();
}

void ModRepository::clear()
{
    for(ModRepositoryEntry * entry : m_entries)
    {
        delete entry;
    }

    m_entries.clear();
    m_updates.clear();

    triggerNeedsUpdate();
}

void ModRepository::setStatus(const RepositoryStatus &status)
{
    if(m_status != status)
    {
        RepositoryStatus old_status = m_status;

        m_status = status;

        if(status == RepositoryIdle)
        {
            emit endedWorking();
        }
        else if(old_status == RepositoryIdle)
        {
            emit startedWorking();
        }
    }

}

void ModRepository::repositoryUpdateLoadRepositories()
{
    setStatus(RepositoryDownloadingData);

    for(const DownloadManager::DownloadItem & item : m_downloadManager->getDownloadedItems())
    {
        QString repository_config = QString::fromUtf8(item.data).trimmed();

        if(repository_config.startsWith("#Silverplum_Repository"))
        {
            for(QString line : repository_config.split(QRegExp("[\r\n]"), QString::SkipEmptyParts))
            {
                if(line.startsWith("#"))
                    continue;

                QStringList cell = line.split("\t");

                if(cell.size() < 4)
                {
                    getLogger().log(Logger::Warning, "modrepository", "update-repository", "load-repository-source", "Invalid entry: " + line);
                    continue;
                }

                ModRepositoryEntry * entry = new ModRepositoryEntry(this);
                entry->setRepositorySourceURL(item.url);
                entry->setId(m_entries.size());
                entry->setModConfigURL(QUrl::fromEncoded(cell[0].toLocal8Bit()));
                entry->setModIconURL(QUrl::fromEncoded(cell[1].toLocal8Bit()));
                entry->setModDescriptionURL(QUrl::fromEncoded(cell[2].toLocal8Bit()));
                entry->setModDownloadURL(QUrl::fromEncoded(cell[3].toLocal8Bit()));

                if(!entry->modConfigURL().isValid())
                {
                    getLogger().log(Logger::Warning, "modrepository", "update-repository", "load-repository-source", "Entry " + line + " has invalid mod config URL. Skipping.");
                    delete entry;
                    continue;
                }

                if(!entry->modDownloadURL().isValid())
                {
                    getLogger().log(Logger::Warning, "modrepository", "update-repository", "load-repository-source", "Entry " + line + " has invalid mod download URL. Skipping.");
                    delete entry;
                    continue;
                }

                m_entries << entry;
            }
        }
    }

    // Start download of entry data
    m_downloadManager->clearDownloadedItems();
    QList<DownloadManager::DownloadItem> items;

    for(ModRepositoryEntry * entry : m_entries)
    {
        if(entry->modConfigURL().isValid())
        {
            DownloadManager::DownloadItem dwn(entry->modConfigURL());
            dwn.source = entry->id();
            dwn.purpose = DownloadPurposeModConfig;

            items << dwn;
        }
        if(entry->modDescriptionURL().isValid())
        {
            DownloadManager::DownloadItem dwn(entry->modDescriptionURL());
            dwn.source = entry->id();
            dwn.purpose = DownloadPurposeModDescription;

            items << dwn;
        }
        if(entry->modIconURL().isValid())
        {
            DownloadManager::DownloadItem dwn(entry->modIconURL());
            dwn.source = entry->id();
            dwn.purpose = DownloadPurposeModIcon;

            items << dwn;
        }
    }

    m_downloadManager->append(items);
}

void ModRepository::repositoryUpdateLoadData()
{
    for(ModRepositoryEntry * entry : QList<ModRepositoryEntry*>(m_entries))
    {
        QString mod_config;
        QString mod_description;
        QPixmap mod_icon;

        for(const DownloadManager::DownloadItem & item : m_downloadManager->getDownloadedItems())
        {
            if(item.source == entry->id() && item.purpose == DownloadPurposeModConfig)
            {
                mod_config = QString::fromUtf8(item.data);
            }
            else if(item.source == entry->id() && item.purpose == DownloadPurposeModDescription)
            {
                mod_description = QString::fromUtf8(item.data);
            }
            else if(item.source == entry->id() && item.purpose == DownloadPurposeModIcon)
            {
                mod_icon.loadFromData(item.data);
            }
        }

        if(!entry->loadModification(mod_config, mod_description))
        {
            getLogger().log(Logger::Warning, "modrepository", "update-repository", "load-entry-data", "An entry failed to initialize! Skipping it.");

            m_entries.removeAll(entry);
            delete entry;
        }
    }

    lookForUpdates();

    setStatus(RepositoryIdle);
    m_needsUpdate = false;
    emit repositoryUpdated(true);
}

void ModRepository::repositoryInstallDownloadedMods()
{
    // First install updates
    for(const DownloadManager::DownloadItem & item : m_downloadManager->getDownloadedItems())
    {
        if(item.purpose == DownloadPurposeModDownloadUpdate)
        {
            getModManager()->importModFromZip(item.filePath, true, false);
        }
    }

    for(const DownloadManager::DownloadItem & item : m_downloadManager->getDownloadedItems())
    {
        if(item.purpose == DownloadPurposeModDownloadInstall)
        {
            getModManager()->importModFromZip(item.filePath);
        }
    }

    m_downloadManager->clearDownloadedItems();

    setStatus(RepositoryIdle);
}

void ModRepository::lookForUpdates()
{
    m_updates.clear();

    QMap<QString, ModRepositoryEntry *> newest;

    for(ModRepositoryEntry * entry : m_entries)
    {
        QString id = entry->modification()->id();

        if(!newest.contains(id) || newest[id]->modification()->version() < entry->modification()->version())
            newest[id] = entry;
    }

    for(ModRepositoryEntry * entry : newest.values())
    {
        Modification * installed = entry->getInstalledMod();

        if(installed != nullptr)
        {
            if(entry->modification()->version() > installed->version())
                m_updates << entry;
        }
    }
}

void ModRepository::downloadsFinished()
{
    switch (m_status)
    {
    case RepositoryDownloadingRepositories:
        repositoryUpdateLoadRepositories();
        break;
    case RepositoryDownloadingData:
        repositoryUpdateLoadData();
        break;
    case RepositoryDownloadingMod:
        repositoryInstallDownloadedMods();
        break;
    default:
        break;
    }
}

bool ModRepository::isWorking() const
{
    return m_status != RepositoryIdle;
}

QStringList ModRepository::getRepositoryURLs()
{
    QStringList result;

    for(Modification * mod : m_modManager->getModifications())
    {
        for(Pipeline * pip : mod->getPipelines())
        {
            if(pip->pipelineMainType() == Pipeline::RepositoryPipeline && pip->isEnabled())
            {
                result << pip->repositories();
            }
        }
    }

    return result;
}

void ModRepository::updateRepository()
{
    if(m_status != RepositoryIdle)
        return;

    clear();

    getLogger().log(Logger::Info, "modrepository", "update-repository", "", "Starting up update repository");

    setStatus(RepositoryDownloadingRepositories);

    m_downloadManager->cancelDownloads();

    QList<DownloadManager::DownloadItem> items;

    for(QString str : getRepositoryURLs())
    {
        QUrl url = QUrl::fromEncoded(str.toLocal8Bit());

        if(url.isValid())
        {
            items << DownloadManager::DownloadItem(url);

            getLogger().log(Logger::Info, "modrepository", "update-repository", "fetch-urls", "Repository URL: " + url.toEncoded());
        }
        else
        {
            getLogger().log(Logger::Warning, "modrepository", "update-repository", "fetch-urls", "Invalid URL: " + str);
        }
    }

    m_downloadManager->append(items);
}
