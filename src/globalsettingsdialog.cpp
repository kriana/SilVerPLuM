#include "globalsettingsdialog.h"
#include "ui_globalsettingsdialog.h"
#include "globalsettings.h"

GlobalSettingsDialog::GlobalSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlobalSettingsDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    ui->appName->setText(QApplication::applicationName());
    ui->appVersion->setText(QApplication::applicationVersion());

    connect(ui->programsMSBUILD, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    connect(ui->programsNuget, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    connect(ui->modsRedirectXNA, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modsForceUnsupported, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modsEnableFileGuard, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modDisablePrimeCache, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modEnableDepCheck, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modDepCheckPriorityAware, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->runningBackupSDVSavegames, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->runningBackupProfileSavegames, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(saveOrDiscart(QAbstractButton*)));

    discart();
}

GlobalSettingsDialog::~GlobalSettingsDialog()
{
    delete ui;
}

void GlobalSettingsDialog::discart()
{
    ui->programsMSBUILD->setCurrentPath(GlobalSettings::instance()->getProgramMSBUILD());
    ui->programsNuget->setCurrentPath(GlobalSettings::instance()->getProgramNuget());
    ui->modsRedirectXNA->setChecked(GlobalSettings::instance()->getDLLRedirectXNA());
    ui->modsForceUnsupported->setChecked(GlobalSettings::instance()->getForceUnsupported());
    ui->modDisablePrimeCache->setChecked(!GlobalSettings::instance()->getEnablePrimeCache());
    ui->modsEnableFileGuard->setChecked(GlobalSettings::instance()->getEnableFileGuard());
    ui->modEnableDepCheck->setChecked(GlobalSettings::instance()->getEnableDepencencyCheck());
    ui->modDepCheckPriorityAware->setChecked(GlobalSettings::instance()->getEnableDepencyCheckPriorityAwareness());
    ui->runningBackupSDVSavegames->setChecked(GlobalSettings::instance()->getRunningBackupSDVSavegames());
    ui->runningBackupProfileSavegames->setChecked(GlobalSettings::instance()->getRunningBackupProfileSavegames());

    ui->buttonBox->hide();
}

void GlobalSettingsDialog::save()
{
    GlobalSettings::instance()->setProgramMSBUILD(ui->programsMSBUILD->getCurrentPath());
    GlobalSettings::instance()->setProgramNuget(ui->programsNuget->getCurrentPath());
    GlobalSettings::instance()->setDLLRedirectXNA(ui->modsRedirectXNA->isChecked());
    GlobalSettings::instance()->setForceUnsupported(ui->modsForceUnsupported->isChecked());
    GlobalSettings::instance()->setEnablePrimeCache(!ui->modDisablePrimeCache->isChecked());
    GlobalSettings::instance()->setEnableFileGuard(ui->modsEnableFileGuard->isChecked());
    GlobalSettings::instance()->setEnableDependencyCheck(ui->modEnableDepCheck->isChecked());
    GlobalSettings::instance()->setEnableDepencyCheckPriorityAwareness(ui->modDepCheckPriorityAware->isChecked());
    GlobalSettings::instance()->setRunningBackupSDVSavegames(ui->runningBackupSDVSavegames->isChecked());
    GlobalSettings::instance()->setRunningBackupProfileSavegames(ui->runningBackupProfileSavegames->isChecked());

    discart();
}

void GlobalSettingsDialog::saveOrDiscart(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::ApplyRole:
        save();
        break;
    case QDialogButtonBox::DestructiveRole:
        discart();
        break;
    default:
        break;
    }
}
