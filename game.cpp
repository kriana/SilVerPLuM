#include "game.h"
#include <QDebug>
#include "utils.h"
#include "profile.h"
#include <QTemporaryDir>
#include <QMessageBox>

Game * Game::m_pInstance = nullptr;

Game::Game()
{
    connect(&m_prepareWatcher, SIGNAL(finished()), this, SLOT(run()));
    connect(&m_postWatcher, SIGNAL(finished()), this, SLOT(finish()));
}

int Game::exitCode() const
{
    return m_exitCode;
}

Game *Game::instance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new Game();
    }

    return m_pInstance;
}

Game::~Game()
{

}

bool Game::running()
{
    return m_Running;
}

void Game::setLauncher(Launcher *l)
{
    if(running())
        throw std::runtime_error("Game is running!");

    m_Launcher = l;
    disconnect(l, SIGNAL(finished(int)), this, SLOT(gameFinished(int)));
    connect(l, SIGNAL(finished(int)), this, SLOT(gameFinished(int)));
}

void Game::prepareAndRun()
{
    if(m_Running)
        throw std::runtime_error("Game already running!");

    m_Running = true;
    emit running(m_Running);

    m_prepareWatcher.setFuture(QtConcurrent::run(this, &Game::prepare));
}

void Game::log(const QString &text)
{
    qInfo() << text;
    emit logged(text);
}

void Game::progress(bool enabled, int _min, int _max, int _val)
{
    emit progressed(enabled, _min, _max, _val);
}

void Game::prepare()
{
    QDir sdvdir = m_Launcher->profile()->StardewValleyDir();
    QDir sdvcontentdir = sdvdir.absoluteFilePath("Content");
    QDir sdvcontentbackup = sdvdir.absoluteFilePath("Content.mod_backup");
    QDir sdvsavegames = Profile::StardewValleySavegameDir();

    log("[1/3] Preparing game data ...");
    log("Backing up Content directory ...");
    progress(true, 0, 6, 1);
    if(sdvcontentbackup.exists())
    {
        log("Warning: Content backup directory already exists. Deleting it now!");
        sdvcontentbackup.removeRecursively();
    }

    progress(true, 0, 6, 2);
    utils::copyDirectory(sdvcontentdir, sdvcontentbackup , true);

    log("Copying savegames from profile ...");

    progress(true, 0, 6, 3);
    QTemporaryDir savegamebackups;

    if(savegamebackups.isValid())
    {
        if(!utils::directoryEmpty(sdvsavegames))
        {
            log("Existing savegames will be backed up to " + savegamebackups.path());
            progress(true, 0, 6, 4);
            utils::copyDirectory(sdvsavegames, savegamebackups.path(), true);

            savegamebackups.setAutoRemove(false);
        }

        progress(true, 0, 6, 5);
        utils::clearDirectory(sdvsavegames);
    }
    else
    {
        qWarning() << "Could not backup savegames. Refusing to clear directory.";
    }

    progress(true, 0, 6, 6);
    utils::copyDirectory(m_Launcher->profile()->profileSavegameDir(), sdvsavegames, true);

}

void Game::run()
{
    log("[2/3] Running game ...");
    progress(false, 0, 0, 0);
    m_Launcher->start();
}

void Game::post()
{
    log("[3/3] Post-game actions ...");

    log("Copying savegames to profile ...");
    progress(true, 0, 5, 1);
    QDir sdvsavegames = Profile::StardewValleySavegameDir();

    QTemporaryDir savegamebackups;
    progress(true, 0, 5, 2);    

    if(savegamebackups.isValid() && !utils::directoryEmpty(m_Launcher->profile()->profileSavegameDir()))
    {
        savegamebackups.setAutoRemove(false);
        log("Existing savegames will be backed up to " + savegamebackups.path());
        progress(true, 0, 5, 3);

        utils::copyDirectory(m_Launcher->profile()->profileSavegameDir(), savegamebackups.path(), true);
        utils::clearDirectory(m_Launcher->profile()->profileSavegameDir());
    }
    else
    {
        qWarning() << "Could not backup savegames. Refusing to clear directory.";
    }

    progress(true, 0, 5, 4);
    utils::copyDirectory(sdvsavegames, m_Launcher->profile()->profileSavegameDir(), true);

    log("Restoring content folder ...");
    QDir sdvdir = m_Launcher->profile()->StardewValleyDir();
    QDir sdvcontentdir = sdvdir.absoluteFilePath("Content");
    QDir sdvcontentbackup = sdvdir.absoluteFilePath("Content.mod_backup");

    if(sdvcontentbackup.exists())
    {
        progress(true, 0, 5, 5);
        sdvcontentdir.removeRecursively();
        sdvdir.rename(sdvcontentbackup.dirName(), sdvcontentdir.dirName());
    }
    else
    {
        qWarning() << "Backup does not exist! Please do not interfere with those processes or you'll lose data!";
    }
}

void Game::finish()
{
    log("[] Finished. Last exit code is " + QString::number(m_exitCode));

    m_Running = false;
    emit running(m_Running);
}

void Game::gameFinished(int retcode)
{
    m_exitCode = retcode;
    m_postWatcher.setFuture(QtConcurrent::run(this, &Game::post));
}
