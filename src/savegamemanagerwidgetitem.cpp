#include "savegamemanagerwidgetitem.h"
#include "ui_savegamemanagerwidgetitem.h"
#include <QMenu>
#include"savegamemanagerwidgetbackupitem.h"
#include "utils.h"
#include <QMessageBox>
#include <QInputDialog>
#include "profilemanager.h"

SavegameManagerWidgetItem::SavegameManagerWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavegameManagerWidgetItem)
{
    ui->setupUi(this);

    QMenu *backup_menu = new QMenu(ui->btnBackup);
    backup_menu->addActions(QList<QAction*>() << ui->actionExport << ui->actionCopyTo << ui->actionSingleOut << ui->actionPrune << ui->actionDeleteMainSavegame << ui->actionDelete);
    ui->btnBackup->setMenu(backup_menu);

    connect(ui->btnBackup, &QToolButton::clicked, this, &SavegameManagerWidgetItem::savegameBackup);
    connect(ui->actionDelete, &QAction::triggered, this, &SavegameManagerWidgetItem::savegameDelete);
    connect(ui->actionDeleteMainSavegame, &QAction::triggered, this, &SavegameManagerWidgetItem::savegameDeleteMain);
    connect(ui->actionCopyTo, &QAction::triggered, this, &SavegameManagerWidgetItem::savegameCopyTo);
    connect(ui->actionSingleOut, &QAction::triggered, this, &SavegameManagerWidgetItem::savegameSingle);
    connect(ui->actionPrune, &QAction::triggered, this, &SavegameManagerWidgetItem::savegamePrune);
    connect(ui->actionExport, &QAction::triggered, this, &SavegameManagerWidgetItem::savegameExport);

    connect(ui->btnShowMore, SIGNAL(toggled(bool)), this, SLOT(showMoreToggled(bool)));
    ui->expandWidget->hide();
}

SavegameManagerWidgetItem::~SavegameManagerWidgetItem()
{
    delete ui;
}

BackupSavegame *SavegameManagerWidgetItem::savegame() const
{
    return m_savegame;
}

void SavegameManagerWidgetItem::setSavegame(BackupSavegame *savegame)
{
    if(m_savegame != nullptr)
    {
        disconnect(m_savegame,
                   &BackupSavegame::backupListChanged,
                   this,
                   &SavegameManagerWidgetItem::reloadList);
        disconnect(m_savegame,
                   &BackupSavegame::mainSavegameChanged,
                   this,
                   &SavegameManagerWidgetItem::updateData);
    }

    m_savegame = savegame;

    if(m_savegame != nullptr)
    {
        connect(m_savegame,
                   &BackupSavegame::backupListChanged,
                   this,
                   &SavegameManagerWidgetItem::reloadList);
        connect(m_savegame,
                   &BackupSavegame::mainSavegameChanged,
                   this,
                   &SavegameManagerWidgetItem::updateData);
    }

    reloadList();
}

void SavegameManagerWidgetItem::updateData()
{
    if(m_savegame != nullptr)
    {
        ui->lblId->setText(m_savegame->id());

        if(m_savegame->getMainSavegame() != nullptr)
        {
            ui->lblFarmerName->setText(m_savegame->getMainSavegame()->name());
            ui->lblIngameDate->setText(m_savegame->getMainSavegame()->timedate());
            ui->lblMoney->setText(QString("%1 G").arg(m_savegame->getMainSavegame()->money()));
            ui->lblFarmName->setText(m_savegame->getMainSavegame()->farmName() + " Farm");


            if(!m_savegame->getBackupSavegames().isEmpty())
                ui->lblBackupInfo->setText(QString::number(m_savegame->getBackupSavegames().size()) + " backups");
            else
                ui->lblBackupInfo->setText("No backups");
        }
        else
        {
            ui->lblFarmerName->setText("Deleted savegame");
            ui->lblIngameDate->setText("You can still restore backups");
            ui->lblMoney->setText("");
            ui->lblFarmName->setText("");

            ui->lblBackupInfo->setText(QString::number(m_savegame->getBackupSavegames().size()) + " backups");
        }
    }
}

void SavegameManagerWidgetItem::reloadList()
{
    utils::clearLayout(ui->backupItems->layout());

    QLayout * layout = ui->backupItems->layout();

    if(m_savegame != nullptr)
    {
        for(Savegame * sav : m_savegame->getBackupSavegames())
        {
            SavegameManagerWidgetBackupItem * item = new SavegameManagerWidgetBackupItem(ui->backupItems);
            item->setSavegame(m_savegame, sav);
            layout->addWidget(item);
        }
    }

    updateData();
}

void SavegameManagerWidgetItem::showMoreToggled(bool toggle)
{
    ui->expandWidget->setVisible(toggle);
}

void SavegameManagerWidgetItem::savegameBackup()
{
    if(m_savegame->getMainSavegame() == nullptr)
    {
        QMessageBox::information(this, "Backup", "Cannot create a backup of a deleted savegame!", QMessageBox::Ok);
        return;
    }

    if(m_savegame->savegameManager()->profile()->checkForExistingBackups())
    {
        if(!m_savegame->backupUseful())
        {
            if(QMessageBox::question(this,
                                     "Backup",
                                     "It seems that there's already a backup with the exact same files. Backup anyways?") == QMessageBox::No)
            {
                return;
            }
        }
    }

    if(!m_savegame->backup())
    {
        QMessageBox::critical(this, "Backup", "Backup was not successful. Please check the profile log at 'Play'.");
    }
}

void SavegameManagerWidgetItem::savegameDelete()
{
    if(QMessageBox::question(this, "Delete whole savegame", "Do you really want to delete this savegame AND backups?") == QMessageBox::Yes)
    {
        m_savegame->deleteAll();
    }
}

void SavegameManagerWidgetItem::savegameDeleteMain()
{
    if(m_savegame->getMainSavegame() == nullptr)
    {
        QMessageBox::information(this, "Delete savegame", "Cannot delete a deleted savegame!", QMessageBox::Ok);
        return;
    }
    if(QMessageBox::question(this, "Delete savegame", "Do you really want to delete this savegame? Backups won't be affected.") == QMessageBox::Yes)
    {
        m_savegame->deleteSavegame(m_savegame->getMainSavegame());
    }
}

void SavegameManagerWidgetItem::savegameCopyTo()
{
    QStringList profiles;

    for(Profile * p : ProfileManager::instance()->getProfiles())
    {
        if(p != m_savegame->savegameManager()->profile())
        {
            profiles << p->name() + " (" + p->id() + ")";
        }
    }

    if(profiles.isEmpty())
    {
        QMessageBox::information(this, "Copy savegame to ...", "You don't have other profiles.", QMessageBox::Ok);
        return;
    }

    QInputDialog dlg;
    dlg.setInputMode(QInputDialog::TextInput);
    dlg.setOption(QInputDialog::UseListViewForComboBoxItems, true);
    dlg.setComboBoxItems(profiles);
    dlg.setLabelText("Select the profile where the savegame should be copied to:");

    if(m_savegame->getMainSavegame() == nullptr)
    {
        dlg.setOkButtonText("Copy backups");
    }
    else
    {
        dlg.setOkButtonText("Copy savegame and backups");
    }

    if(dlg.exec() == QInputDialog::Accepted)
    {
        QString profileid = dlg.textValue().split(" ").last();
        profileid = profileid.mid(1, profileid.size() - 2);
        Profile * p = ProfileManager::instance()->getProfile(profileid);

        if(p == nullptr)
        {
            throw std::runtime_error("Implementation fail!");
        }

        if(p->getSavegameManager()->getSavegameIds().contains(m_savegame->id()))
        {
            QMessageBox overwritedlg;
            overwritedlg.setText("Copy to ...");
            overwritedlg.setInformativeText("There is already a savegame with the same name. What do you want to do?");
            overwritedlg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            overwritedlg.setButtonText(QMessageBox::Yes, "Overwrite");
            overwritedlg.setButtonText(QMessageBox::No, "Rename");

            int action = overwritedlg.exec();

            switch(action)
            {
            case QMessageBox::Yes:

                // Delete the existing one and copy
                p->getSavegameManager()->getSavegame(m_savegame->id())->deleteAll();
                m_savegame->copyTo(p);

                break;
            case QMessageBox::No:

                // Find a new name
                m_savegame->copyTo(p, BackupSavegame::findNewIdFor(m_savegame, p->getSavegameManager()->getSavegameIds()));

                break;
            case QMessageBox::Cancel:
                return;
            }

        }
        else
        {
            m_savegame->copyTo(p);
        }
    }
}

void SavegameManagerWidgetItem::savegameSingle()
{
    if(m_savegame->getMainSavegame() == nullptr)
    {
        QMessageBox::information(this, "Single out", "Cannot create a copy of a deleted savegame!", QMessageBox::Ok);
        return;
    }

    m_savegame->single(m_savegame->getMainSavegame());
}

void SavegameManagerWidgetItem::savegamePrune()
{
    if(QMessageBox::question(this, "Delete duplicate backups", "Do you really want to delete all backups determined as duplicate?") == QMessageBox::Yes)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        m_savegame->pruneBackups();

        QApplication::restoreOverrideCursor();
    }
}

void SavegameManagerWidgetItem::savegameExport()
{
    if(m_savegame->getMainSavegame() == nullptr)
    {
        QMessageBox::information(this, "Single out", "Cannot export a deleted savegame!", QMessageBox::Ok);
        return;
    }

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
                                     "Export savegame",
                                     "Do you want to overwrite " + file + "?") != QMessageBox::Yes)
            {
                return;
            }
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        if(!m_savegame->getMainSavegame()->exportToZip(file))
        {
            QMessageBox::critical(this,
                                  "Export profile",
                                  "Error while exporting!");
        }

        QApplication::restoreOverrideCursor();
    }
}
