#include "developerlauncherdialog.h"
#include "ui_developerlauncherdialog.h"
#include <QPushButton>
#include "profile.h"
#include "profilemanager.h"
#include "logviewer.h"
#include "game.h"

DeveloperLauncherDialog::DeveloperLauncherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeveloperLauncherDialog)
{
    ui->setupUi(this);

    ui->sdvApplicationDirectory->setReadOnly(true);
    ui->sdvContentDirectory->setReadOnly(true);
    ui->sdvSavegameDirectory->setReadOnly(true);
    ui->sdvUserDataDirectory->setReadOnly(true);
    ui->spProfileDirectory->setReadOnly(true);
    ui->spBackupDirectory->setReadOnly(true);
    ui->spCacheDirectory->setReadOnly(true);

    connect(ui->btnClose, &QPushButton::clicked, this, &DeveloperLauncherDialog::accept);
    connect(ui->btnCloseToLog, &QPushButton::clicked, this, &DeveloperLauncherDialog::reject);
    connect(ui->btnShowLog, &QPushButton::clicked, this, &DeveloperLauncherDialog::showProfileLogClicked);
    connect(ui->btnOpenFolders, &QPushButton::clicked, this, &DeveloperLauncherDialog::openFolderClicked);

    ui->sdvApplicationDirectory->setCurrentPath(getProfile()->StardewValleyDir().absolutePath());
    ui->sdvContentDirectory->setCurrentPath(getProfile()->StardewValleyContentDir().absolutePath());
    ui->sdvSavegameDirectory->setCurrentPath(getProfile()->StardewValleySavegameDir().absolutePath());
    ui->sdvUserDataDirectory->setCurrentPath(getProfile()->StardewValleyUserDataDir().absolutePath());
    ui->spProfileDirectory->setCurrentPath(getProfile()->profileBaseDir().absolutePath());
    ui->spBackupDirectory->setCurrentPath(Game::instance()->sdvSavegameBackupDir().absolutePath());
    ui->spCacheDirectory->setCurrentPath(Game::instance()->getCacheDir().absolutePath());

    ui->tabWidget->setCurrentWidget(ui->tabOverview);
}

DeveloperLauncherDialog::~DeveloperLauncherDialog()
{
    delete ui;
}

Profile *DeveloperLauncherDialog::getProfile()
{
    return ProfileManager::instance()->getSelectedProfile();
}

void DeveloperLauncherDialog::showProfileLogClicked()
{
    LogViewer::execForProfile(getProfile());
}

void DeveloperLauncherDialog::openFolderClicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabFolders);
}
