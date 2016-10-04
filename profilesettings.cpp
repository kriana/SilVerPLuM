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

    //Events for dynamic button box
    connect(ui->profileName, SIGNAL(textEdited(QString)), ui->buttonBox, SLOT(show()));
    connect(ui->profileDescription, SIGNAL(textChanged()), ui->buttonBox, SLOT(show()));
    connect(ui->sdvApplicationDirectory, SIGNAL(changed()), ui->buttonBox, SLOT(show()));

    // Change some widget settings
    ui->sdvApplicationDirectory->getFileDialog()->setFileMode(QFileDialog::DirectoryOnly);
    ui->sdvSavegameDirectory->setReadOnly(true);
    ui->profileDirectory->setReadOnly(true);
}

ProfileSettings::~ProfileSettings()
{
    delete ui;
}

void ProfileSettings::setCurrentProfile(Profile *profile)
{
    m_CurrentProfile = profile;
    discart();
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
    bool enabled = m_CurrentProfile != nullptr;

    ui->buttonBox->setEnabled(enabled);
    ui->profileName->setEnabled(enabled);
    ui->profileDescription->setEnabled(enabled);
    ui->profileDirectory->setEnabled(enabled);
    ui->sdvApplicationDirectory->setEnabled(enabled);
    ui->sdvSavegameDirectory->setEnabled(enabled);

    ui->profileName->setText(enabled ? m_CurrentProfile->name() : "");
    ui->profileDescription->document()->setPlainText(enabled ? m_CurrentProfile->description() : "");
    ui->profileDirectory->setCurrentPath(enabled ? m_CurrentProfile->profileBaseDir().absolutePath() : "");
    ui->sdvApplicationDirectory->setCurrentPath(enabled ? m_CurrentProfile->StardewValleyDir().absolutePath() : "");
    ui->sdvSavegameDirectory->setCurrentPath(m_CurrentProfile->StardewValleySavegameDir().absolutePath());

    // Launchers

    utils::clearLayout(ui->launchersLauncherList->layout());
    utils::clearLayout(ui->launchersToolList->layout());

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

    ui->buttonBox->hide();
}

void ProfileSettings::save()
{
    m_CurrentProfile->setName(ui->profileName->text().trimmed());
    m_CurrentProfile->setDescription(ui->profileDescription->document()->toPlainText());
    m_CurrentProfile->setStardewValleyDir(ui->sdvApplicationDirectory->getCurrentPath());

    for(QRadioButton * btn : ui->launchersLauncherList->findChildren<QRadioButton*>())
    {
        if(btn->isChecked())
        {
            m_CurrentProfile->setLauncher(btn->property("launcher").toString());
        }
    }

    discart(); // Reload to be sure
}
