#include "modrepository.h"
#include "modmanager.h"
#include <QRegExp>

ModRepository::ModRepository(ModManager *mgr) : QObject(mgr), m_modManager(mgr)
{
    triggerNeedsUpdate();

    m_downloadManager = new DownloadManager(this);

    connect(mgr, SIGNAL(updatedModList()), this, SLOT(triggerNeedsUpdate()));
    connect(mgr, SIGNAL(updatedModStatus(QString,QString,bool)), this, SLOT(triggerNeedsUpdate()));

    connect(m_downloadManager, SIGNAL(finished()), this, SLOT(downloadsFinished()));
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
            for(QString line : repository_config.split("\n"))
            {

            }
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
