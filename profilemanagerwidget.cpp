#include "profilemanagerwidget.h"
#include "ui_profilemanagerwidget.h"
#include <QInputDialog>
#include <QMessageBox>

ProfileManagerWidget::ProfileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileManagerWidget)
{
    ui->setupUi(this);

    connect(ProfileManager::instance(), &ProfileManager::updated, this, &ProfileManagerWidget::profilesUpdated);
    connect(ProfileManager::instance(), &ProfileManager::selected, this, &ProfileManagerWidget::profileSelected);
    connect(ui->configProfileList, &QListWidget::currentRowChanged, this, &ProfileManagerWidget::selectedProfile);
    connect(ui->profileAdd, &QToolButton::clicked, this, &ProfileManagerWidget::addProfileClicked);
    connect(ui->profileClone, &QToolButton::clicked, this, &ProfileManagerWidget::duplicateProfileClicked);
    connect(ui->profileDelete, &QToolButton::clicked, this, &ProfileManagerWidget::removeProfileClicked);

    profilesUpdated();
}

ProfileManagerWidget::~ProfileManagerWidget()
{
    delete ui;
}

void ProfileManagerWidget::selectedProfile(int index)
{
    if(index >= 0)
    {
        Profile * p = ProfileManager::instance()->getProfiles()[index];
        ProfileManager::instance()->selectProfile(p);
    }
}

void ProfileManagerWidget::profileSelected(Profile *p)
{
    ui->configProfileList->setCurrentRow(ProfileManager::instance()->getProfiles().indexOf(p));
}

void ProfileManagerWidget::profilesUpdated()
{
    ui->configProfileList->clear();

    for(Profile * p : ProfileManager::instance()->getProfiles())
    {
        ui->configProfileList->addItem(p->name());
    }

    profileSelected(ProfileManager::instance()->getSelectedProfile());
}

void ProfileManagerWidget::addProfileClicked()
{
    QString name = QInputDialog::getText(this, "New profile", "Profile name");

    if(!name.isEmpty())
    {
        try
        {
            ProfileManager::instance()->createOrLoadProfile(name);
        }
        catch(...)
        {
            QMessageBox::critical(this, "New profile", "Could not create profile! The name must be a valid folder name and the profile don't have to already exist!");
        }

    }
}

void ProfileManagerWidget::duplicateProfileClicked()
{
    Profile * p = ProfileManager::instance()->getSelectedProfile();
    QString name = QInputDialog::getText(this, "Duplicate profile " + p->name(), "Name of copy");

    if(!name.isEmpty())
    {
        try
        {
            ProfileManager::instance()->duplicateProfile(p, name);
        }
        catch(...)
        {
            QMessageBox::critical(this, "Duplicate profile", "Could not copy profile! The name must be a valid folder name and the profile don't have to already exist!");
        }

    }
}

void ProfileManagerWidget::removeProfileClicked()
{
    Profile * p = ProfileManager::instance()->getSelectedProfile();

    QMessageBox dlg;
    dlg.setText("Delete profile");
    dlg.setInformativeText("Do you really want to delete " + p->name() + "?");
    dlg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dlg.setDefaultButton(QMessageBox::No);

    if(dlg.exec() == QMessageBox::Yes)
    {
        try
        {
            ProfileManager::instance()->deleteProfile(p);
        }
        catch(...)
        {
            QMessageBox::critical(this, "Delete profile", "Could not delete profile! The default profile cannot be deleted.");
        }
    }
}
