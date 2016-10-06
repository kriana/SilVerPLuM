#ifndef GAME_H
#define GAME_H

#include "launcher.h"
#include <QObject>
#include <QtConcurrent>

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

    void log(const QString & text);

    int exitCode() const;

private:

    Game();

    Launcher * m_Launcher;

    bool m_Running = false;

    QFutureWatcher<void> m_prepareWatcher;

    QFutureWatcher<void> m_postWatcher;

    int m_exitCode = 0;

    void progress(bool enabled, int _min = 0, int _max = 0, int _val = 0);    

private slots:

    void gameFinished(int retcode);

    void prepare();

    void run();

    void post();

    void finish();

signals:

    void running(bool running);

    void logged(const QString & text);

    void progressed(bool enabled, int _min, int _max, int _val);
};

#endif // GAME_H
