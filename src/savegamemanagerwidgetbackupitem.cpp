#include "savegamemanagerwidgetbackupitem.h"
#include "ui_savegamemanagerwidgetbackupitem.h"
#include "utils.h"

SavegameManagerWidgetBackupItem::SavegameManagerWidgetBackupItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavegameManagerWidgetBackupItem)
{
    ui->setupUi(this);

    QMenu *backup_menu = new QMenu(ui->btnRestore);
    backup_menu->addActions(QList<QAction*>() << ui->actionCopyTo << ui->actionSingleOut << ui->actionDelete);
    ui->btnRestore->setMenu(backup_menu);

    connect(ui->btnRestore, &QToolButton::clicked, this, &SavegameManagerWidgetBackupItem::savegameRestore);
    connect(ui->actionDelete, &QAction::triggered, this, &SavegameManagerWidgetBackupItem::savegameDelete);
    connect(ui->actionSingleOut, &QAction::triggered, this, &SavegameManagerWidgetBackupItem::savegameSingle);
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

