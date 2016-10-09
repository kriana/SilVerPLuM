#include "game.h"
#include <QDebug>
#include "utils.h"
#include "profile.h"
#include <QTemporaryDir>
#include <QMessageBox>
#include "globalsettings.h"
#include "savegamemanager.h"
Game * Game::m_pInstance = nullptr;

Game::Game()
{
    m_backupTimer = new QTimer();

    connect(&m_prepareWatcher, SIGNAL(finished()), this, SLOT(run()));
    connect(&m_postWatcher, SIGNAL(finished()), this, SLOT(finish()));

    connect(m_backupTimer, SIGNAL(timeout()), this, SLOT(issueFullBackup()));
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
    m_backupTimer->deleteLater();
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

    getLogger().log(Logger::Info, "launcher", "launcher", "", "Start launching of launcher " + m_Launcher->id());

    m_Running = true;
    emit running(m_Running);

    m_prepareWatcher.setFuture(QtConcurrent::run(this, &Game::prepare));
}

void Game::stop()
{
    if(m_Launcher != nullptr)
    {
        m_Launcher->stop();
    }
}

Logger &Game::getLogger()
{
    return m_Launcher->getProfile()->getLogger();
}

void Game::progress(bool enabled, int _min, int _max, int _val)
{
    emit progressed(enabled, _min, _max, _val);
}

void Game::prepareBackupContent(QDir sdvcontentdir, QDir sdvcontentbackup)
{
    getLogger().log(Logger::Info, "launcher", "prepare", "backup-content", "Backing up content directory");

    progress(true, 0, 6, 1);
    if(sdvcontentbackup.exists())
    {
        getLogger().log(Logger::Warning, "launcher", "prepare", "backup-content", "Content backup directory already exists. Deleting it now!");
        sdvcontentbackup.removeRecursively();
    }

    progress(true, 0, 6, 2);
    utils::copyDirectory(sdvcontentdir, sdvcontentbackup , true);

    getLogger().log(Logger::Info, "launcher", "prepare", "backup-content", "Content folder backup created");
}

void Game::prepareCopySavegames(QDir sdvsavegames)
{
    getLogger().log(Logger::Info, "launcher", "prepare", "restore-profile-savegames", "Copying savegames to savegame folder");

    progress(true, 0, 6, 3);
    QTemporaryDir savegamebackups;

    if(savegamebackups.isValid())
    {
        if(GlobalSettings::instance()->getRunningBackupSDVSavegames() && !utils::directoryEmpty(sdvsavegames))
        {
            getLogger().log(Logger::Info, "launcher", "prepare", "restore-profile-savegames", "Existing savegames will be backed up to " + savegamebackups.path());
            progress(true, 0, 6, 4);
            utils::copyDirectory(sdvsavegames, savegamebackups.path(), true);

            savegamebackups.setAutoRemove(false);
        }

        progress(true, 0, 6, 5);
        utils::clearDirectory(sdvsavegames);
    }
    else
    {
        getLogger().log(Logger::Error, "launcher", "prepare", "restore-profile-savegames", "Could not backup savegames. Refusing to clear directory.");
    }

    progress(true, 0, 6, 6);
    utils::copyDirectory(m_Launcher->getProfile()->profileSavegameDir(), sdvsavegames, true);

    getLogger().log(Logger::Info, "launcher", "prepare", "restore-profile-savegames", "Savegames copied");
}

void Game::prepareInstallMods()
{
    getLogger().log(Logger::Info, "launcher", "prepare", "install-mods", "Starting to install mods");

    getLogger().log(Logger::Info, "launcher", "prepare", "install-mods-prime", "Pipelines will be primed for added cross-platform capabilities ...");

    // Call prime(), again, which may be necessary if the user switched OSes
    // Still mod manager widget prime() is important as the user gets direct feedback

    for(Modification * mod : m_Launcher->getProfile()->getModManager()->getModifications())
    {
        mod->prime(false);
    }

    m_Launcher->getProfile()->getModManager()->install();
    getLogger().log(Logger::Info, "launcher", "prepare", "install-mods", "Mods installed");
}

void Game::prepare()
{
    getLogger().log(Logger::Info, "launcher", "prepare", "prepare", "Starting to prepare game and user files");

    QDir sdvdir = m_Launcher->getProfile()->StardewValleyDir();
    QDir sdvcontentdir = sdvdir.absoluteFilePath("Content");
    QDir sdvcontentbackup = sdvdir.absoluteFilePath("Content.mod_backup");
    QDir sdvsavegames = m_Launcher->getProfile()->StardewValleySavegameDir();

    if(m_Launcher->getProfile()->enableBackupOnStart())
    {
        getLogger().log(Logger::Info, "launcher", "prepare", "autobackup-start", "Creating a backup for all savegames");

        issueFullBackup();
    }

    prepareBackupContent(sdvcontentdir, sdvcontentbackup);
    prepareCopySavegames(sdvsavegames);
    prepareInstallMods();

    getLogger().log(Logger::Info, "launcher", "prepare", "prepare", "Preparation ended");
}

void Game::run()
{
    getLogger().log(Logger::Info, "launcher", "run", "run", "Running launcher");
    progress(false, 0, 0, 0);
    m_Launcher->start();

    // Start backup timer
    int interval = m_Launcher->getProfile()->backupInterval();

    if(interval > 0)
    {
        m_backupTimer->start(interval * 1000 * 60);
    }
}

void Game::postMoveSavegames()
{
    getLogger().log(Logger::Info, "launcher", "post", "move-savegames", "Moving savegames back to profile directory");
    progress(true, 0, 5, 1);
    QDir sdvsavegames = m_Launcher->getProfile()->StardewValleySavegameDir();

    QTemporaryDir savegamebackups;
    progress(true, 0, 5, 2);

    if(savegamebackups.isValid())
    {
        if(GlobalSettings::instance()->getRunningBackupProfileSavegames() &&
                !utils::directoryEmpty(m_Launcher->getProfile()->profileSavegameDir()))
        {
            savegamebackups.setAutoRemove(false);
            getLogger().log(Logger::Info, "launcher", "post", "move-savegames", "Existing savegames will be backed up to " + savegamebackups.path());

            progress(true, 0, 5, 3);

            utils::copyDirectory(m_Launcher->getProfile()->profileSavegameDir(), savegamebackups.path(), true);
        }

        utils::clearDirectory(m_Launcher->getProfile()->profileSavegameDir());
    }
    else
    {
        getLogger().log(Logger::Error, "launcher", "post", "move-savegames", "Could not backup savegames. Refusing to clear directory.");
    }

    progress(true, 0, 5, 4);
    utils::copyDirectory(sdvsavegames, m_Launcher->getProfile()->profileSavegameDir(), true);

    getLogger().log(Logger::Info, "launcher", "post", "move-savegames", "Savegames moved");
}

void Game::postRestoreContent()
{
    getLogger().log(Logger::Info, "launcher", "post", "restore-content", "Starting to restore content directory");
    QDir sdvdir = m_Launcher->getProfile()->StardewValleyDir();
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
        getLogger().log(Logger::Error, "launcher", "post", "restore-content", "Backup does not exist! Please do not interfere with those processes or you'll lose data!");
    }
}

void Game::postUninstallMods()
{
    getLogger().log(Logger::Info, "launcher", "post", "uninstall-mods", "Beginning to uninstall mods");
    m_Launcher->getProfile()->getModManager()->uninstall();
    getLogger().log(Logger::Info, "launcher", "post", "uninstall-mods", "Mods have been uninstalled");
}

void Game::post()
{
    getLogger().log(Logger::Info, "launcher", "post", "post", "Beginning post-launch actions");

    postMoveSavegames();

    postUninstallMods();

    postRestoreContent();

    if(m_Launcher->getProfile()->checkForExistingBackups())
    {
        getLogger().log(Logger::Info, "launcher", "prepare", "autobackup-pos-prune", "Clearing away unnecessary backups");

        issueBackupPrune();
    }
}

void Game::finish()
{
    getLogger().log(Logger::Info, "launcher", "post", "finish", "Launcher finished operation with exit code " + QString::number(m_exitCode));

    m_Launcher->getProfile()->getSavegameManager()->reloadSavegames(); // May have added savegames

    m_Running = false;
    emit running(m_Running);
}

void Game::issueFullBackup()
{
    if(!m_Running)
        return;

    getLogger().log(Logger::Info, "launcher", "post", "auto-backup", "Issuing full-backup");
    for(BackupSavegame * sav : m_Launcher->getProfile()->getSavegameManager()->getSavegames().values())
    {
        // If check disabled or useful
        if(!m_Launcher->getProfile()->checkForExistingBackups() ||  sav->backupUseful())
        {
            sav->backup();
        }
    }
}

void Game::issueBackupPrune()
{
    if(!m_Running)
        return;

    getLogger().log(Logger::Info, "launcher", "post", "auto-backup", "Issuing prune-backup");
    for(BackupSavegame * sav : m_Launcher->getProfile()->getSavegameManager()->getSavegames().values())
    {
        sav->pruneBackups();
    }
}

void Game::gameFinished(int retcode)
{
    if(retcode != 0)
    {
        if(Platform::getCurrentPlatform() != Platform::Windows)
        {
            // The Mono kickstarter script leads to 137 error code on Linux/Mac (?)
            if(retcode != 137)
            {
                m_exitCode = retcode;
            }
        }
        else
        {
            m_exitCode = retcode;
        }
    }

    // Stop timer
    m_backupTimer->stop();

    m_postWatcher.setFuture(QtConcurrent::run(this, &Game::post));
}
