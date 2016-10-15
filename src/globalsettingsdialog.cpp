#include "globalsettingsdialog.h"
#include "ui_globalsettingsdialog.h"
#include "globalsettings.h"
#include "utils.h"

GlobalSettingsDialog::GlobalSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlobalSettingsDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);

    ui->appName->setText(QApplication::applicationName());
    ui->appVersion->setText(QApplication::applicationVersion());

    connect(ui->modsRedirectXNA, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modsForceUnsupported, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modsEnableFileGuard, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modDisablePrimeCache, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modEnableDepCheck, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->modDepCheckPriorityAware, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->runningBackupSDVSavegames, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->runningBackupProfileSavegames, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(saveOrDiscart(QAbstractButton*)));
    connect(ui->btnAddProgram, &QPushButton::clicked, this, &GlobalSettingsDialog::addProgramEntry);

    discart();
}

GlobalSettingsDialog::~GlobalSettingsDialog()
{
    delete ui;
}

void GlobalSettingsDialog::discart()
{  
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    ui->modsRedirectXNA->setChecked(GlobalSettings::instance()->getDLLRedirectXNA());
    ui->modsForceUnsupported->setChecked(GlobalSettings::instance()->getForceUnsupported());
    ui->modDisablePrimeCache->setChecked(!GlobalSettings::instance()->getEnablePrimeCache());
    ui->modsEnableFileGuard->setChecked(GlobalSettings::instance()->getEnableFileGuard());
    ui->modEnableDepCheck->setChecked(GlobalSettings::instance()->getEnableDepencencyCheck());
    ui->modDepCheckPriorityAware->setChecked(GlobalSettings::instance()->getEnableDepencyCheckPriorityAwareness());
    ui->runningBackupSDVSavegames->setChecked(GlobalSettings::instance()->getRunningBackupSDVSavegames());
    ui->runningBackupProfileSavegames->setChecked(GlobalSettings::instance()->getRunningBackupProfileSavegames());

    m_externalProgramWidgets.clear();
    utils::clearLayout(ui->externalProgramsList->layout());
    for(QString id : GlobalSettings::instance()->getExternalProgramIds())
    {
        auto * widget = addProgramEntry();
        widget->fillWith(id);

        connect(widget, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    }

    ui->buttonBox->hide();

    QApplication::restoreOverrideCursor();
}

void GlobalSettingsDialog::save()
{   
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();


    GlobalSettings::instance()->setDLLRedirectXNA(ui->modsRedirectXNA->isChecked());
    GlobalSettings::instance()->setForceUnsupported(ui->modsForceUnsupported->isChecked());
    GlobalSettings::instance()->setEnablePrimeCache(!ui->modDisablePrimeCache->isChecked());
    GlobalSettings::instance()->setEnableFileGuard(ui->modsEnableFileGuard->isChecked());
    GlobalSettings::instance()->setEnableDependencyCheck(ui->modEnableDepCheck->isChecked());
    GlobalSettings::instance()->setEnableDepencyCheckPriorityAwareness(ui->modDepCheckPriorityAware->isChecked());
    GlobalSettings::instance()->setRunningBackupSDVSavegames(ui->runningBackupSDVSavegames->isChecked());
    GlobalSettings::instance()->setRunningBackupProfileSavegames(ui->runningBackupProfileSavegames->isChecked());

    for(QString id : GlobalSettings::instance()->getExternalProgramIds())
    {
       GlobalSettings::instance()->removeExternalProgram(id);
    }

    for(auto * widget : m_externalProgramWidgets)
    {
        QString programid = widget->getExternalProgramId();
        ExternalProgram program = widget->getExternalProgram();

        if(!programid.isEmpty() && program.isEmpty())
        {
            GlobalSettings::instance()->setExternalProgram(programid, program);
        }
    }

    QApplication::restoreOverrideCursor();

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

ExternalProgramSettingsWidget * GlobalSettingsDialog::addProgramEntry()
{
    ExternalProgramSettingsWidget * widget = new ExternalProgramSettingsWidget(ui->externalProgramsList);

    connect(widget, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    ui->externalProgramsList->layout()->addWidget(widget);

    m_externalProgramWidgets << widget;

    return widget;
}
