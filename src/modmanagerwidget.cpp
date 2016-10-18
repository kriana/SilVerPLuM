#include "modmanagerwidget.h"
#include "ui_modmanagerwidget.h"
#include "utils.h"
#include "modmanager.h"
#include "modmanagerwidgetitem.h"
#include <QFileDialog>
#include <QMenu>
#include "modimporter.h"

ModManagerWidget::ModManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidget)
{
    ui->setupUi(this);

    connect(ui->searchBar, SIGNAL(textChanged(QString)), this, SLOT(search(QString)));
    connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(refreshList()));
    connect(ui->btnInstallMod, &QToolButton::clicked, this, &ModManagerWidget::installModClicked);
    connect(ui->actionReloadMods, &QAction::triggered, this, &ModManagerWidget::reloadAllMods);
    connect(ui->actionImportMod, &QAction::triggered, this, &ModManagerWidget::importModClicked);

    QMenu * refresh_menu = new QMenu(ui->btnRefresh);
    refresh_menu->addAction(ui->actionReloadMods);
    ui->btnRefresh->setMenu(refresh_menu);

    QMenu * add_menu = new QMenu(ui->btnInstallMod);
    add_menu->addAction(ui->actionImportMod);
    ui->btnInstallMod->setMenu(add_menu);
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

    utils::clearLayout(ui->modList->layout());


    QVBoxLayout * layout = dynamic_cast<QVBoxLayout*>(ui->modList->layout());

    if(m_currentMM != nullptr)
    {
        for(Modification * mod : m_currentMM->getModifications())
        {
            ModManagerWidgetItem * item = new ModManagerWidgetItem(ui->modList);
            item->setCurrentModification(mod);
            layout->addWidget(item);
        }
    }

    layout->addStretch(1);


    search(ui->searchBar->text());
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

void ModManagerWidget::search(const QString &searchstring_)
{
    QString searchstring = searchstring_.trimmed();

    QLayout * layout = ui->modList->layout();

    for(int i = 0; i < layout->count(); ++i)
    {
        QLayoutItem * item = layout->itemAt(i);

        if(item->widget() != nullptr)
        {
            ModManagerWidgetItem * mitem = dynamic_cast<ModManagerWidgetItem*>(item->widget());

            if(mitem != nullptr)
            {
                mitem->search(searchstring);
            }
        }
    }
}
