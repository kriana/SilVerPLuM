#include "profilesettings.h"
#include "ui_profilesettings.h"
#include "profilemanager.h"
#include "utils.h"
#include "game.h"

ProfileSettings::ProfileSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileSettings)
{
    ui->setupUi(this);

    // Connect events
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &ProfileSettings::saveOrDiscart);
    connect(ui->btnSDVAutodetect, &QPushButton::clicked, this, &ProfileSettings::autodetectSDV);

    //Events for dynamic button box
    connect(ui->profileName, SIGNAL(textEdited(QString)), ui->buttonBox, SLOT(show()));
    connect(ui->profileDescription, SIGNAL(textChanged()), ui->buttonBox, SLOT(show()));
    connect(ui->sdvApplicationDirectory, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    connect(ui->sdvSavegameDirectory, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    connect(ui->sdvUserDataDirectory, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    connect(ui->sdvContentDirectory, SIGNAL(changed()), ui->buttonBox, SLOT(show()));
    connect(ui->sdvVersion, SIGNAL(currentTextChanged(QString)), ui->buttonBox, SLOT(show()));
    connect(ui->sdvTechXNA, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->sdvTechMonoGame, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->backupBeforeStart, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));
    connect(ui->backupInterval, SIGNAL(valueChanged(int)), ui->buttonBox, SLOT(show()));
    connect(ui->backupCheckExisting, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));

    // Change some widget settings
    ui->sdvApplicationDirectory->getFileDialog()->setFileMode(QFileDialog::DirectoryOnly);    
    ui->sdvSavegameDirectory->getFileDialog()->setFileMode(QFileDialog::DirectoryOnly);
    ui->sdvUserDataDirectory->getFileDialog()->setFileMode(QFileDialog::DirectoryOnly);
    ui->sdvContentDirectory->getFileDialog()->setFileMode(QFileDialog::DirectoryOnly);
    ui->profileDirectory->setReadOnly(true);

    // add versions
    for(QString version : Profile::StardewValleyVersions())
    {
        ui->sdvVersion->addItem(version);
    }

    ui->gameRunningMessage->setText(tr("The settings are locked while the game is running"));
    connect(Game::instance(), SIGNAL(running(bool)), this, SLOT(gameRunning(bool)));
}

ProfileSettings::~ProfileSettings()
{
    delete ui;
}

void ProfileSettings::setCurrentProfile(Profile *profile)
{
    if(saving)
        return;

    if(profile != m_CurrentProfile)
    {
        if(m_CurrentProfile != nullptr)
        {
            disconnect(m_CurrentProfile,
                       SIGNAL(updated()),
                       this,
                       SLOT(discart()));
        }

        m_CurrentProfile = profile;

        if(m_CurrentProfile != nullptr)
        {
            connect(m_CurrentProfile,
                       SIGNAL(updated()),
                       this,
                       SLOT(discart()));
        }

        discart();
    }
}

void ProfileSettings::saveOrDiscart(QAbstractButton *button)
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

void ProfileSettings::discart()
{
    if(saving)
        return;

    setEnabled(m_CurrentProfile != nullptr);

    if(m_CurrentProfile != nullptr)
    {
        ui->profileName->setText(m_CurrentProfile->name());
        ui->profileDescription->document()->setPlainText(m_CurrentProfile->description());
        ui->profileDirectory->setCurrentPath(m_CurrentProfile->profileBaseDir().absolutePath());
        ui->sdvApplicationDirectory->setCurrentPath(m_CurrentProfile->StardewValleyDir().absolutePath());
        ui->sdvContentDirectory->setCurrentPath(m_CurrentProfile->StardewValleyContentDir().absolutePath());
        ui->sdvSavegameDirectory->setCurrentPath(m_CurrentProfile->StardewValleySavegameDir().absolutePath());
        ui->sdvUserDataDirectory->setCurrentPath(m_CurrentProfile->StardewValleyUserDataDir().absolutePath());
        ui->sdvVersion->setCurrentText(m_CurrentProfile->StardewValleyVersion().toString());
        ui->backupBeforeStart->setChecked(m_CurrentProfile->enableBackupOnStart());
        ui->backupInterval->setValue(m_CurrentProfile->backupInterval());
        ui->backupCheckExisting->setChecked(m_CurrentProfile->checkForExistingBackups());

        switch(m_CurrentProfile->StardewValleyTechnology())
        {
        case Platform::GameTechnologyXNA:
            ui->sdvTechXNA->setChecked(true);
            break;
        case Platform::GameTechnologyMonoGame:
            ui->sdvTechMonoGame->setChecked(true);
            break;
        }
    }

    // Launchers

    utils::clearLayout(ui->launchersLauncherList->layout());

    if(m_CurrentProfile != nullptr)
    {
        for(Launcher * l : m_CurrentProfile->getLaunchers())
        {
            QRadioButton * btn = new QRadioButton(ui->launchersLauncherList);
            btn->setText(l->name() + "\n" + l->description());
            btn->setProperty("launcher", l->id());
            btn->setAutoExclusive(true);

            connect(btn, SIGNAL(toggled(bool)), ui->buttonBox, SLOT(show()));

            ui->launchersLauncherList->layout()->addWidget(btn);

            if(l == m_CurrentProfile->getLauncher())
            {
                btn->setChecked(true);
            }
        }
    }

    ui->buttonBox->hide();
}

void ProfileSettings::save()
{
    if(saving)
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    saving = true;
    m_CurrentProfile->setUpdateBatch(true);

    m_CurrentProfile->setName(ui->profileName->text().trimmed());
    m_CurrentProfile->setDescription(ui->profileDescription->document()->toPlainText());
    m_CurrentProfile->setStardewValleyDir(ui->sdvApplicationDirectory->getCurrentPath());
    m_CurrentProfile->setStardewValleyContentDir(ui->sdvContentDirectory->getCurrentPath());
    m_CurrentProfile->setStardewValleySavegameDir(ui->sdvSavegameDirectory->getCurrentPath());
    m_CurrentProfile->setStardewValleyUserDataDir(ui->sdvUserDataDirectory->getCurrentPath());
    m_CurrentProfile->setStardewValleyVersion(QVersionNumber::fromString(ui->sdvVersion->currentText()));
    m_CurrentProfile->setEnableBackupOnStart(ui->backupBeforeStart->isChecked());
    m_CurrentProfile->setBackupInterval(ui->backupInterval->value());
    m_CurrentProfile->setCheckForExistingBackups(ui->backupCheckExisting->isChecked());

    if(ui->sdvTechXNA->isChecked())
        m_CurrentProfile->setStardewValleyTechnology(Platform::GameTechnologyXNA);
    else if(ui->sdvTechMonoGame->isChecked())
        m_CurrentProfile->setStardewValleyTechnology(Platform::GameTechnologyMonoGame);

    for(QRadioButton * btn : ui->launchersLauncherList->findChildren<QRadioButton*>())
    {
        if(btn->isChecked())
        {
            m_CurrentProfile->setLauncher(btn->property("launcher").toString());
        }
    }

    m_CurrentProfile->setUpdateBatch(false);
    saving = false;

    discart(); // Reload to be sure

    QApplication::restoreOverrideCursor();
}

void ProfileSettings::autodetectSDV()
{
    // For now: Reset to defaults
    ui->sdvApplicationDirectory->setCurrentPath(Profile::DefaultStardewValleyDir().absolutePath());
    ui->sdvContentDirectory->setCurrentPath(Profile::DefaultStardewValleyContentDir().absolutePath());
    ui->sdvSavegameDirectory->setCurrentPath(Profile::DefaultStardewValleySavegameDir().absolutePath());
    ui->sdvUserDataDirectory->setCurrentPath(Profile::DefaultStardewValleyUserDataDir().absolutePath());
    ui->sdvVersion->setCurrentText("0");

    switch(Profile::DefaultStardewValleyTechnology())
    {
    case Platform::GameTechnologyXNA:
        ui->sdvTechXNA->setChecked(true);
        break;
    case Platform::GameTechnologyMonoGame:
        ui->sdvTechMonoGame->setChecked(true);
        break;
    }
}

void ProfileSettings::gameRunning(bool running)
{
    setDisabled(running);
    ui->gameRunningMessage->setVisible(running);
}
