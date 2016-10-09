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

    static Game * m_pInstance;

public:

    static Game * instance();

    ~Game();

    bool running();

    void setLauncher(Launcher * l);

    void prepareAndRun();

    int exitCode() const;

    Logger & getLogger();

private:

    Game();

    Launcher * m_Launcher;

    QTimer * m_backupTimer;

    bool m_Running = false;

    QFutureWatcher<void> m_prepareWatcher;

    QFutureWatcher<void> m_postWatcher;

    int m_exitCode = 0;

    void progress(bool enabled, int _min = 0, int _max = 0, int _val = 0);    

    void prepareBackupContent(QDir sdvcontentdir, QDir sdvcontentbackup);

    void prepareCopySavegames(QDir sdvsavegames);

    void postMoveSavegames();

    void postRestoreContent();

    void prepareInstallMods();

    void postUninstallMods();

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
