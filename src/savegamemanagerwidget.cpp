#include "savegamemanagerwidget.h"
#include "ui_savegamemanagerwidget.h"
#include "utils.h"
#include "savegamemanagerwidgetitem.h"
#include <QMenu>

SavegameManagerWidget::SavegameManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavegameManagerWidget)
{
    ui->setupUi(this);

    connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(reloadList()));
    connect(ui->btnImport, SIGNAL(clicked(bool)), this, SLOT(importSavegame()));
    connect(ui->actionReloadSavegames, &QAction::triggered, this, &SavegameManagerWidget::reloadAllSavegames);

    QMenu * refresh_menu = new QMenu(ui->btnRefresh);
    refresh_menu->addAction(ui->actionReloadSavegames);
    ui->btnRefresh->setMenu(refresh_menu);
}

SavegameManagerWidget::~SavegameManagerWidget()
{
    delete ui;
}

SavegameManager *SavegameManagerWidget::savegameManager() const
{
    return m_savegameManager;
}

void SavegameManagerWidget::setSavegameManager(SavegameManager *savegameManager)
{
    if(m_savegameManager != nullptr)
    {
        disconnect(m_savegameManager,
                   &SavegameManager::updatedSavegames,
                   this,
                   &SavegameManagerWidget::reloadList);
    }

    m_savegameManager = savegameManager;

    if(m_savegameManager != nullptr)
    {
        connect(m_savegameManager,
                   &SavegameManager::updatedSavegames,
                   this,
                   &SavegameManagerWidget::reloadList);
    }

    reloadList();
}

void SavegameManagerWidget::reloadList()
{
    int scrollh =ui->scrollArea->horizontalScrollBar()->value();
    int scrollv = ui->scrollArea->verticalScrollBar()->value();

    utils::clearLayout(ui->savegameItems->layout());

    QVBoxLayout * layout = dynamic_cast<QVBoxLayout*>(ui->savegameItems->layout());

    if(m_savegameManager != nullptr)
    {
        for(BackupSavegame * sav : m_savegameManager->getSavegames().values())
        {
            SavegameManagerWidgetItem * item = new SavegameManagerWidgetItem(ui->savegameItems);
            item->setSavegame(sav);
            layout->addWidget(item);
        }
    }

    layout->addStretch(1);

    ui->scrollArea->horizontalScrollBar()->setValue(scrollh);
    ui->scrollArea->verticalScrollBar()->setValue(scrollv);
}

void SavegameManagerWidget::reloadAllSavegames()
{
    if(m_savegameManager != nullptr)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();
        m_savegameManager->reloadSavegames();
        QApplication::restoreOverrideCursor();
    }
}

void SavegameManagerWidget::importSavegame()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::ExistingFiles);
    dlg.setMimeTypeFilters(QStringList() << "application/zip" << "application/octet-stream");

    if(dlg.exec() == QFileDialog::Accepted)
    {
        for(QString file : dlg.selectedFiles())
        {
            if(!m_savegameManager->import(file))
            {
                if(QMessageBox::critical(this,
                                      "Import savegame",
                                      "Could not import " + file,
                                      QMessageBox::Ok,
                                      QMessageBox::Cancel) == QMessageBox::Cancel)
                {
                    break;
                }
            }
        }
    }
}
