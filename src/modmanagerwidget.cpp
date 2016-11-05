#include "modmanagerwidget.h"
#include "ui_modmanagerwidget.h"
#include "utils.h"
#include "modmanager.h"
#include "modmanagerwidgetitem.h"
#include <QFileDialog>
#include <QMenu>
#include "modimporter.h"
#include "modrepositorywindow.h"
#include "game.h"

ModManagerWidget::ModManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidget)
{
    ui->setupUi(this);

    connect(ui->searchBar, SIGNAL(textChanged(QString)), this, SLOT(triggerSearchFilter()));
    connect(ui->categoryFilter, SIGNAL(selectedCategory(QString)), this, SLOT(triggerSearchFilter()));
    connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(refreshList()));
    connect(ui->btnInstallMod, &QToolButton::clicked, this, &ModManagerWidget::installModClicked);
    connect(ui->btnDownloadMod, &QToolButton::clicked, this, &ModManagerWidget::repositoryClicked);
    connect(ui->actionReloadMods, &QAction::triggered, this, &ModManagerWidget::reloadAllMods);
    connect(ui->actionImportMod, &QAction::triggered, this, &ModManagerWidget::importModClicked);
    connect(ui->actionAddDefaultMods, &QAction::triggered, this, &ModManagerWidget::addDefaultModsClicked);

    QMenu * refresh_menu = new QMenu(ui->btnRefresh);
    refresh_menu->addAction(ui->actionReloadMods);
    ui->btnRefresh->setMenu(refresh_menu);

    QMenu * add_menu = new QMenu(ui->btnInstallMod);
    add_menu->addAction(ui->actionImportMod);
    add_menu->addAction(ui->actionAddDefaultMods);
    ui->btnInstallMod->setMenu(add_menu);

    setAcceptDrops(true);

    ui->gameRunningMessage->setText(tr("The mod manager is locked while the game is running"));
    connect(Game::instance(), SIGNAL(running(bool)), this, SLOT(gameRunning(bool)));
}

ModManagerWidget::~ModManagerWidget()
{
    delete ui;
}

ModManager *ModManagerWidget::currentModManager() const
{
    return m_currentMM;
}

void ModManagerWidget::setModManager(ModManager *currentMM)
{
    if(m_currentMM != nullptr)
    {
        disconnect(m_currentMM, SIGNAL(updatedModList()), this, SLOT(refreshList()));
        disconnect(m_currentMM->profile(), SIGNAL(updatedSettings()), this, SLOT(refreshList()));
    }

    m_currentMM = currentMM;
    ui->modList->setModManager(currentMM);

    if(m_currentMM != nullptr)
    {
        connect(m_currentMM, SIGNAL(updatedModList()), this, SLOT(refreshList()));
        connect(m_currentMM->profile(), SIGNAL(updatedSettings()), this, SLOT(refreshList()));
    }

    ui->dependencyWarning->setModManager(currentMM);

    refreshList();

    ui->searchBar->setText("");
}

void ModManagerWidget::refreshList()
{
    int scrollh =ui->scrollArea->horizontalScrollBar()->value();
    int scrollv = ui->scrollArea->verticalScrollBar()->value();

    ui->modList->refreshList();


    triggerSearchFilter();
    ui->scrollArea->horizontalScrollBar()->setValue(scrollh);
    ui->scrollArea->verticalScrollBar()->setValue(scrollv);

    if(m_currentMM->getUnloadableModPaths().isEmpty())
    {
        ui->message->hide();
    }
    else
    {
        ui->message->message(QString("Could not load %1 mods. Check the profile log for more information.").arg(m_currentMM->getUnloadableModPaths().size()));
    }

    ui->categoryFilter->fillWith(m_currentMM->getModifications());
}

void ModManagerWidget::reloadAllMods()
{
    if(m_currentMM != nullptr)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();
        m_currentMM->reloadMods();
        QApplication::restoreOverrideCursor();
    }
}

void ModManagerWidget::importModClicked()
{
    ModImporter dlg;
    dlg.exec();
}

void ModManagerWidget::installModClicked()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::ExistingFiles);
    dlg.setMimeTypeFilters(QStringList() << "application/zip" << "application/octet-stream");

    if(dlg.exec() == QFileDialog::Accepted)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        for(QString file : dlg.selectedFiles())
        {
            if(!m_currentMM->importModFromZip(file))
            {
                if(QMessageBox::critical(this,
                                      "Add modification",
                                      "Could not add " + file + ". Such mods need to be compatible with SilVerPLuM. You can try out the mod importer in the menu that opens if you click the arrow next to 'Add mod'.",
                                      QMessageBox::Ok,
                                      QMessageBox::Cancel) == QMessageBox::Cancel)
                {
                    break;
                }
            }           
        }

        QApplication::restoreOverrideCursor();
    }
}

void ModManagerWidget::repositoryClicked()
{
    ModRepositoryWindow dlg;
    dlg.exec();
}

void ModManagerWidget::triggerSearchFilter()
{
    ui->modList->searchFilter(ui->searchBar->text(), ui->categoryFilter->currentCategory());
}

void ModManagerWidget::gameRunning(bool running)
{
    setDisabled(running);
    ui->gameRunningMessage->setVisible(running);
}

void ModManagerWidget::addDefaultModsClicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    m_currentMM->importDefaultMods();

    QApplication::restoreOverrideCursor();
}
