#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "profilemanager.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QMenu>
#include "globalsettings.h"
#include "globalsettingsdialog.h"
#include "utils.h"
#include "logviewer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect events   
    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::playClicked);    
    connect(ui->playLogClose, &QPushButton::clicked, this, &MainWindow::closeLogClicked);
    connect(ui->btnApplicationSettings, &QPushButton::clicked, this, &MainWindow::openApplicationSettings);
    connect(ui->btnShowLog, &QPushButton::clicked, this, &MainWindow::openProfileLog);   

    // Update splitter
    ui->splitter->setSizes(QList<int>() << 100 << 500);
    ui->splitter_2->setSizes(QList<int>() << 100 << 500);
    ui->splitter_3->setSizes(QList<int>() << 100 << 500);

    // UI lazyness
    ui->mainTabWidget->setCurrentWidget(ui->tabPlay);
    ui->playStackedWidget->setCurrentWidget(ui->playLauncherPage);

    // Restore state
    GlobalSettings::instance()->getWindowState(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play(Launcher *l)
{
    ui->playLogLog->clear();
    qRegisterMetaType<Logger::Entry>();
    connect(&ProfileManager::instance()->getSelectedProfile()->getLogger(),
            &Logger::logged,
            this,
            &MainWindow::gameLog,
            Qt::QueuedConnection);
    QApplication::processEvents();

    Game::instance()->setLauncher(l);
    Game::instance()->prepareAndRun();
}

void MainWindow::playClicked()
{
    play(ProfileManager::instance()->getSelectedProfile()->getLauncher());
}

void MainWindow::playSubActionTriggered()
{
    QAction * action = dynamic_cast<QAction*>(sender());
    if(action != nullptr)
    {
        if(action->property("launcher-type") == "launcher")
        {
            Launcher * l = ProfileManager::instance()->getSelectedProfile()->getLauncher(action->property("launcher-id").toString());

            if(l != nullptr)
            {
                play(l);
            }
        }
    }
}

void MainWindow::cmbSelectedProfile(int index)
{
    if(index != -1 && !m_profilesLoading)
    {
        Profile * p = ProfileManager::instance()->getProfiles()[index];
        ProfileManager::instance()->selectProfile(p);
    }
}

void MainWindow::profileSelected(Profile *p)
{
    ui->cmbProfile->setCurrentIndex(ProfileManager::instance()->getProfiles().indexOf(p));

    // Populate menu

    if(ui->btnPlay->menu() != nullptr)
    {
        delete ui->btnPlay->menu();
        ui->btnPlay->setMenu(nullptr);
    }

    QMenu * play_menu = new QMenu(ui->btnPlay);
    bool populated = false;

    for(Launcher * l : ProfileManager::instance()->getSelectedProfile()->getLaunchers())
    {
        QAction * action = play_menu->addAction(l->name());
        action->setProperty("launcher-type", "launcher");
        action->setProperty("launcher-id", l->id());

        populated = true;

        connect(action, &QAction::triggered, this, &MainWindow::playSubActionTriggered);
    }

    ui->btnPlay->setMenu(populated ? play_menu : nullptr);
    ui->btnPlay->setPopupMode(populated ? QToolButton::MenuButtonPopup : QToolButton::DelayedPopup);

    // Set matching views
    ui->configProfileConfig->setCurrentProfile(p);
    ui->modManager->setModManager(p->getModManager());
    ui->savegameManager->setSavegameManager(p->getSavegameManager());

    updateLauncherInfo();

    connect(p, &Profile::updated, this, &MainWindow::updateLauncherInfo, Qt::UniqueConnection);
}

void MainWindow::profilesUpdated()
{
    m_profilesLoading = true;

    ui->cmbProfile->clear();

    for(Profile * p : ProfileManager::instance()->getProfiles())
    {
        ui->cmbProfile->addItem(p->name());
    }

    m_profilesLoading = false;
}

void MainWindow::updateLauncherInfo()
{
    // Set profile info in launcher screen
    ui->profileInfo->setText(utils::makeTextEditHTML(utils::markdownToHTML(ProfileManager::instance()->getSelectedProfile()->description())));
}

void MainWindow::gameRunning(bool running)
{
    ui->tabConfigure->setEnabled(!running);
    ui->tabMod->setEnabled(!running);
    ui->playLogClose->setEnabled(!running);
    ui->tabManage->setEnabled(!running);

    if(running)
    {
        ui->playLogLog->clear();
        ui->mainTabWidget->setCurrentWidget(ui->tabPlay);
        ui->playStackedWidget->setCurrentWidget(ui->playLogPage);
    }
    else
    {
        disconnect(&ProfileManager::instance()->getSelectedProfile()->getLogger(),
                &Logger::logged,
                this,
                &MainWindow::gameLog);

        ui->mainTabWidget->setCurrentWidget(ui->tabPlay);

        // Go back if everything is OK
        if(Game::instance()->exitCode() == 0)
            ui->playStackedWidget->setCurrentWidget(ui->playLauncherPage);
    }
}

void MainWindow::gameLog(const Logger::Entry &entry)
{
    ui->playLogLog->addTopLevelItem(new QTreeWidgetItem(ui->playLogLog,
                                                        QStringList() <<
                                                        entry.levelToString() <<
                                                        entry.timestamp.toString() <<
                                                        entry.component <<
                                                        entry.subcomponent <<
                                                        entry.operation <<
                                                        entry.message));
    ui->playLogLog->verticalScrollBar()->setValue(ui->playLogLog->verticalScrollBar()->maximum());
}

void MainWindow::gameProgress(bool enabled, int _min, int _max, int _value)
{
    ui->playLogProgress->setVisible(enabled);
    ui->playLogProgress->setMaximum(_min);
    ui->playLogProgress->setMaximum(_max);
    ui->playLogProgress->setValue(_value);
}

void MainWindow::closeLogClicked()
{
    ui->mainTabWidget->setCurrentWidget(ui->tabPlay);
    ui->playStackedWidget->setCurrentWidget(ui->playLauncherPage);
}

void MainWindow::openApplicationSettings()
{
    GlobalSettingsDialog dlg;
    dlg.exec();

    // Trigger update of mod list
    ui->modManager->refreshList();
}

void MainWindow::openProfileLog()
{
    LogViewer::execForProfile(ProfileManager::instance()->getSelectedProfile());
}

void MainWindow::profilesInitialized()
{
    connect(ProfileManager::instance(), &ProfileManager::updatedProfileList, this, &MainWindow::profilesUpdated);
    connect(ProfileManager::instance(), &ProfileManager::updatedProfileSetting, this, &MainWindow::profilesUpdated);
    connect(ProfileManager::instance(), &ProfileManager::updatedSelection, this, &MainWindow::profileSelected);
    connect(Game::instance(), SIGNAL(running(bool)), this, SLOT(gameRunning(bool)));
    connect(Game::instance(), SIGNAL(progressed(bool,int,int,int)), this, SLOT(gameProgress(bool,int,int,int)));

    profilesUpdated();
    profileSelected(ProfileManager::instance()->getSelectedProfile());

    // Moved to here as it otherwise would reset the profile to default
    connect(ui->cmbProfile, SIGNAL(currentIndexChanged(int)), this, SLOT(cmbSelectedProfile(int)));

    setEnabled(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{    

    if(Game::instance()->running())
    {
        event->ignore();
    }

    GlobalSettings::instance()->setWindowState(this);
}

void MainWindow::showEvent(QShowEvent *event)
{    
    QMainWindow::showEvent(event);

    if(!m_initialized)
    {
        setEnabled(false);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        ProfileManager::instance()->initialize();
        profilesInitialized();

        m_initialized = true;
        QApplication::restoreOverrideCursor();
    }

}


