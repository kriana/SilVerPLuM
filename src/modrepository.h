#ifndef MODREPOSITORY_H
#define MODREPOSITORY_H

#include <QObject>
#include "downloadmanager.h"
#include "logger.h"
#include "modrepositoryentry.h"

class ModManager;

class ModRepository : public QObject
{
    Q_OBJECT
public:

    enum RepositoryStatus
    {
        RepositoryIdle,
        RepositoryDownloadingRepositories,
        RepositoryDownloadingData
    };

    ModRepository(ModManager * mgr);

    /**
     * @brief Returns true if the repository needs an update
     * @return
     */
    bool needsUpdate() const;

    /**
     * @brief Returns true if the repository is currently doing something
     * @return
     */
    bool isWorking() const;

    /**
     * @brief Returns list of all active repository sources
     * @return
     */
    QStringList getRepositoryURLs();

    RepositoryStatus getStatus() const;

    Logger & getLogger();

    void clear();

signals:

    void startedWorking();

    void endedWorking();

    void repositoryNeedsUpdate();

    void repositoryUpdated(bool successful);

public slots:

    void updateRepository();

    void triggerNeedsUpdate();

private:

    ModManager * m_modManager;

    RepositoryStatus m_status = RepositoryIdle;

    bool m_needsUpdate;

    DownloadManager * m_downloadManager;

    QList<ModRepositoryEntry*> m_entries;

    void setStatus(const RepositoryStatus &status);

    void repositoryUpdateLoadRepositories();

private slots:

    void downloadsFinished();
};

#endif // MODREPOSITORY_H
