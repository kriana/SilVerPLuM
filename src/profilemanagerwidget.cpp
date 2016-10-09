#include "profilemanagerwidget.h"
#include "ui_profilemanagerwidget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <QFileDialog>

ProfileManagerWidget::ProfileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileManagerWidget)
{
    ui->setupUi(this);

    connect(ProfileManager::instance(), &ProfileManager::updatedProfileList, this, &ProfileManagerWidget::profilesUpdated);
    connect(ProfileManager::instance(), &ProfileManager::updatedProfileSetting, this, &ProfileManagerWidget::profilesUpdated);
    connect(ProfileManager::instance(), &ProfileManager::updatedSelection, this, &ProfileManagerWidget::profileSelected);
    connect(ui->configProfileList, &QListWidget::currentRowChanged, this, &ProfileManagerWidget::selectedProfile);
    connect(ui->profileAdd, &QToolButton::clicked, this, &ProfileManagerWidget::addProfileClicked);
    connect(ui->profileClone, &QToolButton::clicked, this, &ProfileManagerWidget::duplicateProfileClicked);
    connect(ui->profileDelete, &QToolButton::clicked, this, &ProfileManagerWidget::removeProfileClicked);
    connect(ui->actionImport, &QAction::triggered, this, &ProfileManagerWidget::importProfileClicked);
    connect(ui->btnExport, &QToolButton::clicked, this, &ProfileManagerWidget::exportProfileClicked);

    QMenu * menu = new QMenu(ui->profileAdd);
    menu->addAction(ui->actionImport);
    ui->profileAdd->setMenu(menu);

    profilesUpdated();
}

ProfileManagerWidget::~ProfileManagerWidget()
{
    delete ui;
}

void ProfileManagerWidget::selectedProfile(int index)
{
    if(index >= 0 && !m_loading)
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
    m_loading = true;

    ui->configProfileList->clear();

    for(int i = 0; i < ProfileManager::instance()->getProfiles().size(); ++i)
    {
        Profile * p = ProfileManager::instance()->getProfiles()[i];

        ui->configProfileList->addItem(p->name().isEmpty() ? p->id() : p->name());
    }

    m_loading = false;

    profileSelected(ProfileManager::instance()->getSelectedProfile());
}

void ProfileManagerWidget::addProfileClicked()
{
    QString name = QInputDialog::getText(this, "New profile", "Profile name");

    if(!name.isEmpty())
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        if(ProfileManager::instance()->createOrLoadProfile(name) == nullptr)
        {
            QMessageBox::critical(this, "New profile", "Could not create profile! The name must be a valid folder name and the profile don't have to already exist!");
        }

        QApplication::restoreOverrideCursor();

    }
}

void ProfileManagerWidget::duplicateProfileClicked()
{
    Profile * p = ProfileManager::instance()->getSelectedProfile();
    QString name = QInputDialog::getText(this, "Duplicate profile " + p->name(), "Name of copy");

    if(!name.isEmpty())
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        if(!ProfileManager::instance()->duplicateProfile(p, name))
        {
             QMessageBox::critical(this, "Duplicate profile", "Could not copy profile! The name must be a valid folder name and the profile don't have to already exist!");
        }        

        QApplication::restoreOverrideCursor();

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
        if(!ProfileManager::instance()->deleteProfile(p))
        {
            QMessageBox::critical(this, "Delete profile", "Could not delete profile! The default profile cannot be deleted.");
        }
    }
}

void ProfileManagerWidget::exportProfileClicked()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::AnyFile);
    dlg.setMimeTypeFilters(QStringList() << "application/zip" << "application/octet-stream");
    dlg.setAcceptMode(QFileDialog::AcceptSave);

    if(dlg.exec() == QFileDialog::Accepted)
    {
        QString file = dlg.selectedFiles().first();

        if(QFileInfo(file).exists())
        {
            if(QMessageBox::question(this,
                                     "Export profile",
                                     "Do you want to overwrite " + file + "?") != QMessageBox::Yes)
            {
                return;
            }
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        Profile * p = ProfileManager::instance()->getSelectedProfile();
        if(!ProfileManager::instance()->exportProfile(p, file))
        {
            QMessageBox::critical(this,
                                  "Export profile",
                                  "Error while exporting!");
        }

        QApplication::restoreOverrideCursor();
    }
}

void ProfileManagerWidget::importProfileClicked()
{
    QString name = QInputDialog::getText(this, "Import profile", "Set the name of the imported profile:");

    if(name.isEmpty())
    {
       return;
    }

    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setMimeTypeFilters(QStringList() << "application/zip" << "application/octet-stream");
    dlg.setAcceptMode(QFileDialog::AcceptOpen);

    if(dlg.exec() == QFileDialog::Accepted)
    {
        QString file = dlg.selectedFiles().first();

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        if(!ProfileManager::instance()->importProfile(file, name))
        {
            QMessageBox::critical(this,
                                  "Import profile",
                                  "Error while importing! Open the profile log for more information.");
        }

        QApplication::restoreOverrideCursor();
    }
}
