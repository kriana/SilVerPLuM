#ifndef GAME_H
#define GAME_H

#include "launcher.h"
#include <QObject>
#include <QtConcurrent>
#include "logger.h"
#include <QTimer>

class Game : public QObject
{

    Q_OBJECT

private:

    enum Status
    {
        StatusNotRunning,
        StatusPrepare,
        StatusRun,
        StatusPost
    };

    static Game * m_pInstance;

public:

    static Game * instance();

    ~Game();

    /**
     * @brief Returns true if the game is running
     * @return
     */
    bool running();

    /**
     * @brief Sets the launcher of this game. Will throw an exception if it's still running.
     * @param l
     */
    void setLauncher(Launcher * l);

    /**
     * @brief Runs the current launcher
     */
    void prepareAndRun();

    /**
     * @brief Tries to force-stop the current launcher
     */
    void stop();

    /**
     * @brief Returns the exit-code of the last run
     * @return
     */
    int exitCode() const;

    /**
     * @brief Gets the logger of this game
     * @return
     */
    Logger & getLogger();

    /**
     * @brief Returns all files that are marked as unoverrideable. Should take effect when FileGuard is active.
     * @return
     */
    QSet<QString> getUnoverrideableGameFiles() const;

private:

    Game();

    Launcher * m_Launcher;

    QTimer * m_backupTimer;

    Status m_Status = StatusNotRunning;

    QSet<QString> m_GameFiles;

    QFutureWatcher<void> m_prepareWatcher;

    QFutureWatcher<void> m_postWatcher;

    int m_exitCode = 0;

    /**
     * @brief Sends progress to any listener
     * @param enabled
     * @param _min
     * @param _max
     * @param _val
     */
    void progress(bool enabled, int _min = 0, int _max = 0, int _val = 0);

    /**
     * @brief Determines unoverrideable files in prepare step
     */
    void prepareFindUnoverrideableGameFiles();

    /**
     * @brief Backups the game's content directory
     * @param sdvcontentdir
     * @param sdvcontentbackup
     */
    void prepareBackupContent(QDir sdvcontentdir, QDir sdvcontentbackup);

    /**
     * @brief Copies the profile's savegames into the savegame directory
     * @param sdvsavegames
     */
    void prepareCopySavegames(QDir sdvsavegames);

    /**
     * @brief Moves the savegames from the savegame dir back to the profile dir
     */
    void postMoveSavegames();

    /**
     * @brief Restores the original content directory
     */
    void postRestoreContent();

    /**
     * @brief Installs all activated mods
     */
    void prepareInstallMods();

    /**
     * @brief Uninstalls all activated mods
     */
    void postUninstallMods();

    /**
     * @brief The directory where the savegames are moved before launching
     * @return
     */
    QDir sdvSavegameBackupDir();

    /**
     * @brief The directory where the content is copied before launching
     * @return
     */
    QDir sdvContentBackupDir();

private slots:

    void gameFinished(int retcode);

    void prepare();

    void run();

    void post();

    void finish();

    void issueFullBackup();

    void issueBackupPrune();

signals:

    void running(bool running);

    void progressed(bool enabled, int _min, int _max, int _val);
};

#endif // GAME_H
