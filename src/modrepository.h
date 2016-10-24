#ifndef MODREPOSITORY_H
#define MODREPOSITORY_H

#include <QObject>
#include "downloadmanager.h"
#include "logger.h"
#include "modrepositoryentry.h"
#include <QTemporaryDir>

class ModManager;

class ModRepository : public QObject
{
    Q_OBJECT
public:

    enum RepositoryStatus
    {
        RepositoryIdle,
        RepositoryDownloadingRepositories,
        RepositoryDownloadingData,
        RepositoryDownloadingMod
    };

    enum RepositoryEntryDownloadPurpose
    {
        DownloadPurposeModConfig,
        DownloadPurposeModDescription,
        DownloadPurposeModIcon,
        DownloadPurposeModDownloadInstall,
        DownloadPurposeModDownloadUpdate
    };

    ModRepository(ModManager * mgr);

    ~ModRepository();

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

    QString getModTempDir() const;

    void cancelCurrentAction();

    QList<ModRepositoryEntry *> getUpdates() const;

    QList<ModRepositoryEntry *> getEntries() const;

    ModManager *getModManager() const;

    /**
     * @brief install
     * @param entries
     * @param update Will overwrite files silently
     */
    void install(QList<ModRepositoryEntry *> entries, bool update);

signals:

    void startedWorking();

    void endedWorking();

    void repositoryNeedsUpdate();

    void repositoryUpdated(bool successful);

    void modDownloaded(bool successful);

    void downloadProgress(int _min, int _max, int _value);

public slots:

    void clear();

    void updateRepository();

    void triggerNeedsUpdate();

    void triggerLookForUpdates();

private:

    ModManager * m_modManager;

    RepositoryStatus m_status = RepositoryIdle;

    bool m_needsUpdate;

    DownloadManager * m_downloadManager;

    QList<ModRepositoryEntry*> m_entries;

    QList<ModRepositoryEntry*> m_updates;

    QTemporaryDir m_modTempDir;

    bool m_somethingFailed;

    void setStatus(const RepositoryStatus &status);

    void repositoryUpdateLoadRepositories();

    void repositoryUpdateLoadData();

    void repositoryInstallDownloadedMods();

    void lookForUpdates();

private slots:

    void downloadsFinished();
};

#endif // MODREPOSITORY_H
