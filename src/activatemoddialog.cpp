#include "activatemoddialog.h"
#include "ui_activatemoddialog.h"
#include "modmanager.h"
#include "profile.h"
#include "globalsettings.h"
#include <QScrollBar>
#include <QStackedWidget>
#include <QPushButton>

ActivateModDialog::ActivateModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivateModDialog)
{
    ui->setupUi(this);

    connect(&m_watcher, SIGNAL(finished()), this, SLOT(finishedWorking()));

    connect(ui->btnDependencyIgnore, &QPushButton::clicked, this, &ActivateModDialog::dependcencyIgnoreClicked);
    connect(ui->btnDependencyActivateDependencies, &QPushButton::clicked, &ActivateModDialog::dependcencyActivateClicked);
    connect(ui->btnDependencyCancel, &QPushButton::clicked, this, &ActivateModDialog::reject);

    connect(ui->btnActivationCancel, &QPushButton::clicked, this, &ActivateModDialog::activationCancelClicked);
    connect(ui->btnActivationIgnore, &QPushButton::clicked, this, &ActivateModDialog::activationIgnoreClicked);
    connect(ui->btnActivationRetry, &QPushButton::clicked, this, &ActivateModDialog::activationRetryClicked);
}

ActivateModDialog::~ActivateModDialog()
{
    delete ui;
}

int ActivateModDialog::reininitializeModification(Modification *mod)
{
    m_pipelinesToActivate << mod->getEnabledPipelines();
    m_modManager = mod->getModManager();

    runPreparation();

    return exec();
}

int ActivateModDialog::activateModification(Modification *mod)
{
    m_pipelinesToActivate << mod->getSupportedDefaultPipelines();
    m_modManager = mod->getModManager();

    runPreparation();

    return exec();
}

int ActivateModDialog::activatePipeline(Pipeline *pip)
{
    m_pipelinesToActivate << pip;
    m_modManager = pip->mod()->getModManager();

    runPreparation();

    return exec();
}

void ActivateModDialog::closeEvent(QCloseEvent *event)
{
    if(m_isWorking)
    {
        event->setAccepted(false);
    }
    else
    {
        QDialog::closeEvent(event);
    }
}

bool ActivateModDialog::isWorking() const
{
    return m_isWorking;
}

void ActivateModDialog::setIsWorking(bool isWorking)
{
    m_isWorking = isWorking;
    ui->buttonBox->setVisible(!isWorking);
}

void ActivateModDialog::finishedWorking()
{
    setIsWorking(false);
    int result = m_watcher.result();

    if(result == 0)
    {        
        Pipeline * pip = m_pipelinesToActivate.takeLast();
        pip->setEnabled(true, false);

        if(m_pipelinesToActivate.isEmpty())
            accept();
        else
            runWorkload();
    }
    else
    {

    }
}

void ActivateModDialog::runPreparation()
{
    Modification * mod = m_pipelinesToActivate.first()->mod();
    DependencyTree::DependencyCheckResult result = m_modManager->getDependencyTree()->dependenciesFulfilled(mod,
                                                                                                            false,
                                                                                                            true);
    if(result.satisfied())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageActivation);
        runWorkload();
    }
    else
    {
        ui->stackedWidget->setCurrentWidget(ui->pageDependencyInfo);

        QString html;

        html += "<html><body>";

        html += "<h2>" + mod->name() + " (" + mod->id() + ")" + "</h2>";

        if(!result.missing.isEmpty())
        {
            html += "<h3>Need to be activated</h3>";

            html += "<ul>";

            for(Modification * m : result.missing)
            {
                html += QString("<li>%1 (%2)</li>").arg(m->name()).arg(m->id());
            }

            html += "</ul>";
        }

        if(!result.unresolved.isEmpty())
        {
            html += "<h3>Missing dependencies</h3>";

            html += "<ul>";

            for(Dependency dep : result.unresolved)
            {
                html += QString("<li>%1</li>").arg(dep.toPrettyString());
            }


            html += "</ul>";
        }

        html += "</body></html>";

        ui->lblDependencyInfo->document()->setHtml(html);
        ui->btnDependencyActivateDependencies->setVisible(!result.missing.isEmpty());
    }
}

void ActivateModDialog::runWorkload()
{
    setIsWorking(true);

    QFuture<int> workload = QtConcurrent::run([&]() {
        return m_pipelinesToActivate.last()->primePipeline(m_reinitialize);
     });

    m_watcher.setFuture(workload);
}

void ActivateModDialog::gotLog(const Logger::Entry &entry)
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

void ActivateModDialog::dependcencyActivateClicked()
{
    Modification * mod = m_pipelinesToActivate.first()->mod();
    DependencyTree::DependencyCheckResult result = m_modManager->getDependencyTree()->dependenciesFulfilled(mod,
                                                                                                            false,
                                                                                                            true);
    for(Modification * m : result.missing)
    {
        m_pipelinesToActivate << m->getSupportedDefaultPipelines();
    }

    runWorkload();
}

void ActivateModDialog::dependcencyIgnoreClicked()
{
    runWorkload();
}

void ActivateModDialog::activationIgnoreClicked()
{
    Pipeline * pip = m_pipelinesToActivate.takeLast();
    pip->setEnabled(true, false);

    if(m_pipelinesToActivate.isEmpty())
        accept();
    else
        runWorkload();
}

void ActivateModDialog::activationRetryClicked()
{
    runWorkload();
}

void ActivateModDialog::activationCancelClicked()
{
    reject();
}
