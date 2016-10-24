#include "modrepositorywindow.h"
#include "ui_modrepositorywindow.h"
#include <QPushButton>
#include <QTabWidget>
#include <QStackedWidget>
#include "profile.h"
#include "modification.h"
#include "modmanager.h"
#include "profilemanager.h"
#include <QTreeWidgetItem>
#include <QScrollBar>
#include <QProgressBar>
#include <QLineEdit>
#include "categorycombobox.h"

ModRepositoryWindow::ModRepositoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModRepositoryWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
    ui->tabWidget->setCurrentWidget(ui->tabWelcome);

    connect(ui->btnOverviewDownload, &QPushButton::clicked, this, [&]() {
       ui->tabWidget->setCurrentWidget(ui->tabDownload);
    });
    connect(ui->btnOverviewConfigure, &QPushButton::clicked, this, [&]() {
       ui->tabWidget->setCurrentWidget(ui->tabRepositories);
    });
    connect(ui->btnOverviewUpdate, &QPushButton::clicked, this, [&]() {
       ui->tabWidget->setCurrentWidget(ui->tabUpdate);
    });

    ui->updateMessageWidget->setText(tr("You might need to fetch the list of available mods online. Click on the button right next to this message to do this now."));
    ui->updateMessageWidget->getActionButton()->setText(tr("Fetch repository sources"));
    ui->updateMessageWidget->getActionButton()->setIcon(QIcon::fromTheme("view-refresh"));
    ui->updateMessageWidget->getActionButton()->show();
    connect(getModRepository(), SIGNAL(repositoryUpdated(bool)), ui->updateMessageWidget, SLOT(setHidden(bool)));
    connect(getModRepository(), SIGNAL(repositoryNeedsUpdate()), ui->updateMessageWidget, SLOT(show()));
    connect(getModRepository(), SIGNAL(repositoryUpdated(bool)), this, SLOT(refreshList()));
    connect(getModRepository(), SIGNAL(downloadProgress(int,int,int)), this, SLOT(gotProgress(int,int,int)));
    connect(ui->updateMessageWidget->getActionButton(), SIGNAL(clicked(bool)), this, SLOT(updateRepositoryClicked()));
    connect(ui->progressStop, &QPushButton::clicked, this, &ModRepositoryWindow::cancelClicked);
    connect(ui->btnFetchSources_download, SIGNAL(clicked(bool)), this, SLOT(updateRepositoryClicked()));
    connect(ui->btnFetchSources_update, SIGNAL(clicked(bool)), this, SLOT(updateRepositoryClicked()));
    connect(ui->btnUpgradeAll, SIGNAL(clicked(bool)), this, SLOT(upgradeAllClicked()));

    connect(ui->downloadSearch, SIGNAL(textChanged(QString)), ui->downloadList, SLOT(search(QString)));
    connect(ui->updateSearch, SIGNAL(textChanged(QString)), ui->updateList, SLOT(search(QString)));
    connect(ui->downloadCategoryFilter, SIGNAL(selectedCategory(QString)), ui->downloadList, SLOT(filterCategory(QString)));
    connect(ui->updateCategoryFilter, SIGNAL(selectedCategory(QString)), ui->updateList, SLOT(filterCategory(QString)));

    updatePipelineList();

    if(getModRepository()->needsUpdate())
    {
        ui->updateMessageWidget->show();
    }

    connect(getModRepository(), &ModRepository::startedWorking, this, [&](){
       ui->stackedWidget->setCurrentWidget(ui->progressPage);
    });
    connect(getModRepository(), &ModRepository::endedWorking, this, [&](){
       ui->stackedWidget->setCurrentWidget(ui->mainPage);
    });

    connect(&(getModRepository()->getLogger()), &Logger::logged, this, &ModRepositoryWindow::gotLog);    
    connect(getModRepository()->getModManager(), &ModManager::updatedModList, this, &ModRepositoryWindow::updatePipelineList);

    connect(getModRepository(), SIGNAL(repositoryUpdated(bool)), this, SLOT(showDownloadFailMessage(bool)));
    connect(getModRepository(), SIGNAL(modDownloaded(bool)), this, SLOT(showDownloadFailMessage(bool)));

    refreshList();
}

ModRepositoryWindow::~ModRepositoryWindow()
{
    delete ui;
}

ModRepository *ModRepositoryWindow::getModRepository()
{
    return ProfileManager::instance()->getSelectedProfile()->getModManager()->getModRepository();
}

void ModRepositoryWindow::closeEvent(QCloseEvent *event)
{
    if(getModRepository()->isWorking())
    {
        event->setAccepted(false);
    }
    else
    {
        QDialog::closeEvent(event);
    }
}

void ModRepositoryWindow::cancelClicked()
{
    getModRepository()->cancelCurrentAction();
}

void ModRepositoryWindow::updateRepositoryClicked()
{
    getModRepository()->updateRepository();
}

void ModRepositoryWindow::upgradeAllClicked()
{
    getModRepository()->install(getModRepository()->getUpdates(), true);
}

void ModRepositoryWindow::gotLog(const Logger::Entry &entry)
{
    ui->progressLog->addTopLevelItem(new QTreeWidgetItem(ui->progressLog,
                                                        QStringList() <<
                                                        entry.levelToString() <<
                                                        entry.timestamp.toString() <<
                                                        entry.component <<
                                                        entry.subcomponent <<
                                                        entry.operation <<
                                                        entry.message));
    ui->progressLog->verticalScrollBar()->setValue(ui->progressLog->verticalScrollBar()->maximum());
}

void ModRepositoryWindow::refreshList()
{
    ui->downloadList->setEntryList(getModRepository()->getEntries());
    ui->updateList->setEntryList(getModRepository()->getUpdates());

    QList<Modification*> download_mods;
    QList<Modification*> update_mods;

    for(ModRepositoryEntry * e : getModRepository()->getEntries())
    {
        download_mods << e->modification();
    }
    for(ModRepositoryEntry * e : getModRepository()->getUpdates())
    {
        update_mods << e->modification();
    }

    ui->downloadCategoryFilter->fillWith(download_mods);
    ui->updateCategoryFilter->fillWith(update_mods);
}

void ModRepositoryWindow::gotProgress(int _min, int _max, int _value)
{
    ui->progressProgress->setMinimum(_min);
    ui->progressProgress->setMaximum(_max);
    ui->progressProgress->setValue(_value);
}

void ModRepositoryWindow::showDownloadFailMessage(bool hide)
{
    if(!hide)
    {
        ui->generalMessageWidget->message("Not all downloads were successful. You can find more information in the profile log.");
    }
}

void ModRepositoryWindow::updatePipelineList()
{
    Profile * p = ProfileManager::instance()->getSelectedProfile();

    QList<Pipeline*> sourcepipelines;
    bool some_enabled = false;

    for(Modification * mod : p->getModManager()->getModifications())
    {
        for(Pipeline * pip : mod->getPipelines())
        {
            if(pip->pipelineMainType() == Pipeline::RepositoryPipeline)
            {
                sourcepipelines << pip;

                if(pip->isEnabled())
                    some_enabled = true;
            }
        }
    }

    ui->repositorySourcePipelines->setPipelines(sourcepipelines);

    if(sourcepipelines.isEmpty())
    {
        ui->generalMessageWidget->message(tr("There are no repository sources installed. You won't be able to get mods."));
    }
    else if(!some_enabled)
    {
        ui->generalMessageWidget->message(tr("There is no repository source enabled. Go to 'Configure' and enable one to be able to get mods."));
    }
}
