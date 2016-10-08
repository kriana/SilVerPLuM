#include "profilesettings.h"
#include "ui_profilesettings.h"
#include "profilemanager.h"
#include "utils.h"

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
    connect(ui->sdvVersion, SIGNAL(currentTextChanged(QString)), ui->buttonBox, SLOT(show()));

    // Change some widget settings
    ui->sdvApplicationDirectory->getFileDialog()->setFileMode(QFileDialog::DirectoryOnly);    
    ui->profileDirectory->setReadOnly(true);
}

ProfileSettings::~ProfileSettings()
{
    delete ui;
}

void ProfileSettings::setCurrentProfile(Profile *profile)
{
    if(profile != m_CurrentProfile)
    {
        if(m_CurrentProfile != nullptr)
        {
            disconnect(m_CurrentProfile->getModManager(),
                       SIGNAL(modEnabledDisabled(QString,QString,bool)),
                       this,
                       SLOT(discart()));
        }

        m_CurrentProfile = profile;

        if(m_CurrentProfile != nullptr)
        {
            connect(m_CurrentProfile->getModManager(),
                       SIGNAL(modEnabledDisabled(QString,QString,bool)),
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

    bool enabled = m_CurrentProfile != nullptr;

    ui->buttonBox->setEnabled(enabled);
    ui->profileName->setEnabled(enabled);
    ui->profileDescription->setEnabled(enabled);
    ui->profileDirectory->setEnabled(enabled);
    ui->sdvApplicationDirectory->setEnabled(enabled);
    ui->sdvSavegameDirectory->setEnabled(enabled);
    ui->sdvVersion->setEnabled(enabled);


    ui->profileName->setText(enabled ? m_CurrentProfile->name() : "");
    ui->profileDescription->document()->setPlainText(enabled ? m_CurrentProfile->description() : "");
    ui->profileDirectory->setCurrentPath(enabled ? m_CurrentProfile->profileBaseDir().absolutePath() : "");
    ui->sdvApplicationDirectory->setCurrentPath(enabled ? m_CurrentProfile->StardewValleyDir().absolutePath() : "");
    ui->sdvSavegameDirectory->setCurrentPath(m_CurrentProfile->StardewValleySavegameDir().absolutePath());
    ui->sdvVersion->setCurrentText(m_CurrentProfile->StardewValleyVersion().toString());

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

    m_CurrentProfile->setName(ui->profileName->text().trimmed());
    m_CurrentProfile->setDescription(ui->profileDescription->document()->toPlainText());
    m_CurrentProfile->setStardewValleyDir(ui->sdvApplicationDirectory->getCurrentPath());
    m_CurrentProfile->setStardewValleySavegameDir(ui->sdvSavegameDirectory->getCurrentPath());
    m_CurrentProfile->setStardewValleyVersion(QVersionNumber::fromString(ui->sdvVersion->currentText()));

    for(QRadioButton * btn : ui->launchersLauncherList->findChildren<QRadioButton*>())
    {
        if(btn->isChecked())
        {
            m_CurrentProfile->setLauncher(btn->property("launcher").toString());
        }
    }

    saving = false;

    discart(); // Reload to be sure

    QApplication::restoreOverrideCursor();
}

void ProfileSettings::autodetectSDV()
{
    // For now: Reset to defaults
    ui->sdvApplicationDirectory->setCurrentPath(Profile::DefaultStardewValleyDir().absolutePath());
    ui->sdvSavegameDirectory->setCurrentPath(Profile::DefaultStardewValleySavegameDir().absolutePath());
    ui->sdvVersion->setCurrentText("0");
}
