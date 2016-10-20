#include "modrepositorywindow.h"
#include "ui_modrepositorywindow.h"
#include <QPushButton>
#include <QTabWidget>
#include "profile.h"
#include "modification.h"
#include "modmanager.h"
#include "profilemanager.h"

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

    ui->updateMessageWidget->setText(tr("You might need to fetch the list of available mods online. Click on 'Fetch' to do this now."));
    ui->updateMessageWidget->getActionButton()->setText(tr("Fetch"));
    ui->updateMessageWidget->getActionButton()->setIcon(QIcon::fromTheme("update-none"));
    ui->updateMessageWidget->getActionButton()->show();
    connect(getModRepository(), SIGNAL(repositoryUpdated(bool)), ui->updateMessageWidget, SLOT(setHidden(bool)));
    connect(getModRepository(), SIGNAL(repositoryNeedsUpdate()), ui->updateMessageWidget, SLOT(show()));
    connect(ui->updateMessageWidget->getActionButton(), SIGNAL(clicked(bool)), this, SLOT(updateRepositoryClicked()));

    updatePipelineList();

    if(getModRepository()->needsUpdate())
    {
        ui->updateMessageWidget->show();
    }
}

ModRepositoryWindow::~ModRepositoryWindow()
{
    delete ui;
}

ModRepository *ModRepositoryWindow::getModRepository()
{
    return ProfileManager::instance()->getSelectedProfile()->getModManager()->getModRepository();
}

void ModRepositoryWindow::updateRepositoryClicked()
{
    getModRepository()->updateRepository();
}

void ModRepositoryWindow::updatePipelineList()
{
    Profile * p = ProfileManager::instance()->getSelectedProfile();

    QList<Pipeline*> sourcepipelines;

    for(Modification * mod : p->getModManager()->getModifications())
    {
        for(Pipeline * pip : mod->getPipelines())
        {
            if(pip->pipelineMainType() == Pipeline::RepositoryPipeline)
            {
                sourcepipelines << pip;
            }
        }
    }

    ui->repositorySourcePipelines->setPipelines(sourcepipelines);
}
