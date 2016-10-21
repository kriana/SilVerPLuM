#include "modrepository.h"
#include "modmanager.h"
#include <QRegExp>

ModRepository::ModRepository(ModManager *mgr) : QObject(mgr), m_modManager(mgr)
{
    triggerNeedsUpdate();

    m_downloadManager = new DownloadManager(this);
    m_downloadManager->setLogger(&(getLogger()));

    connect(mgr, SIGNAL(updatedModList()), this, SLOT(triggerNeedsUpdate()));
    connect(mgr, SIGNAL(updatedModStatus(QString,QString,bool)), this, SLOT(triggerNeedsUpdate()));

    connect(m_downloadManager, SIGNAL(finished()), this, SLOT(downloadsFinished()));
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
            DownloadManager::DownloadItem dwn(entry->modConfigURL());
            dwn.source = entry->id();
            dwn.purpose = DownloadPurposeModDescription;

            items << dwn;
        }
    }

    m_downloadManager->append(items);
}

void ModRepository::repositoryUpdateLoadData()
{
    for(ModRepositoryEntry * entry : m_entries)
    {
        QString mod_config;
        QString mod_description;

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

            entry->loadModification(mod_config, mod_description);
        }
    }

    setStatus(RepositoryIdle);
    m_needsUpdate = false;
    emit repositoryUpdated(true);
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
