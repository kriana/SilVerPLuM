#include "activatemoddialog.h"
#include "ui_activatemoddialog.h"
#include "modmanager.h"
#include "profile.h"
#include <QScrollBar>

ActivateModDialog::ActivateModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivateModDialog)
{
    ui->setupUi(this);

    connect(&m_watcher, SIGNAL(finished()), this, SLOT(finishedWorking()));
}

ActivateModDialog::~ActivateModDialog()
{
    delete ui;
}

void ActivateModDialog::reininitializeModification(Modification *mod)
{
    setIsWorking(true);
    m_operation = ReinitializeMod;
    m_currentModification = mod;
    connect(&mod->getLogger(), &Logger::logged, this , &ActivateModDialog::gotLog);

    runWorkload();

    exec();
}

void ActivateModDialog::activateModification(Modification *mod)
{
    setIsWorking(true);
    m_operation = ActivateMod;
    m_currentModification = mod;
    connect(&mod->getLogger(), &Logger::logged, this , &ActivateModDialog::gotLog);

    runWorkload();

    exec();
}

void ActivateModDialog::activatePipeline(Pipeline *pip)
{
    setIsWorking(true);
    m_operation = ActivatePipeline;
    m_currentPipeline = pip;
    connect(&pip->getLogger(), &Logger::logged, this , &ActivateModDialog::gotLog);

    runWorkload();

    exec();
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
    ui->buttonBox->setEnabled(!isWorking);
}

void ActivateModDialog::finishedWorking()
{
    setIsWorking(false);
    int result = m_watcher.result();

    if(result == 0)
    {
        close();
    }
    else
    {

    }
}

void ActivateModDialog::runWorkload()
{
    QFuture<int> workload;

    switch(m_operation)
    {
    case ActivateMod:
        workload = QtConcurrent::run([&]() {
               return m_currentModification->enableDefaults();
            });
        break;
    case ReinitializeMod:
        workload = QtConcurrent::run([&]() {
               return m_currentModification->prime(true);
            });
        break;
    case ActivatePipeline:
        workload = QtConcurrent::run([&]() {
               return m_currentPipeline->setEnabled(true);
            });
        break;
    }

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
