#include "savegamemanagerwidgetbackupitem.h"
#include "ui_savegamemanagerwidgetbackupitem.h"
#include "utils.h"

SavegameManagerWidgetBackupItem::SavegameManagerWidgetBackupItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavegameManagerWidgetBackupItem)
{
    ui->setupUi(this);

    QMenu *backup_menu = new QMenu(ui->btnRestore);
    backup_menu->addActions(QList<QAction*>() << ui->actionExport << ui->actionCopyTo << ui->actionSingleOut << ui->actionDelete);
    ui->btnRestore->setMenu(backup_menu);

    connect(ui->btnRestore, &QToolButton::clicked, this, &SavegameManagerWidgetBackupItem::savegameRestore);
    connect(ui->actionDelete, &QAction::triggered, this, &SavegameManagerWidgetBackupItem::savegameDelete);
    connect(ui->actionSingleOut, &QAction::triggered, this, &SavegameManagerWidgetBackupItem::savegameSingle);
    connect(ui->actionExport, &QAction::triggered, this, &SavegameManagerWidgetBackupItem::savegameExport);
}

SavegameManagerWidgetBackupItem::~SavegameManagerWidgetBackupItem()
{
    delete ui;
}

Savegame *SavegameManagerWidgetBackupItem::savegame() const
{
    return m_savegame;
}

void SavegameManagerWidgetBackupItem::setSavegame(BackupSavegame * parent, Savegame *savegame)
{
    m_parentSavegame = parent;
    m_savegame = savegame;

    if(savegame != nullptr)
    {
        ui->lblDate->setText(QString("Created on %1, %2 G").arg(savegame->backupDate().toString())
                             .arg(savegame->money()));
        ui->lblInfo->setText(QString("%1, %2h played").arg(savegame->timedate()).arg(m_savegame->timePlayedMS() / 1000 / 60 / 60));
    }
}

void SavegameManagerWidgetBackupItem::savegameRestore()
{
    if( m_parentSavegame->getMainSavegame() == nullptr || QMessageBox::question(this, "Restore backup", "Do you really want to restore this backup? You may lose progress.") == QMessageBox::Yes)
    {
        m_parentSavegame->restore(m_savegame);
    }
}

void SavegameManagerWidgetBackupItem::savegameDelete()
{
    if(QMessageBox::question(this, "Delete backup", "Do you really want to delete this savegame backup?") == QMessageBox::Yes)
    {
        m_parentSavegame->deleteSavegame(m_savegame);
    }
}

void SavegameManagerWidgetBackupItem::savegameSingle()
{
    m_parentSavegame->single(m_savegame);
}

void SavegameManagerWidgetBackupItem::savegameExport()
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
                                     "Export savegame",
                                     "Do you want to overwrite " + file + "?") != QMessageBox::Yes)
            {
                return;
            }
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        if(!m_savegame->exportToZip(file))
        {
            QMessageBox::critical(this,
                                  "Export profile",
                                  "Error while exporting!");
        }

        QApplication::restoreOverrideCursor();
    }
}

