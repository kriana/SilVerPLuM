#include "dependencycheckerwidget.h"
#include "ui_dependencycheckerwidget.h"
#include "utils.h"

DependencyCheckerWidget::DependencyCheckerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DependencyCheckerWidget)
{
    ui->setupUi(this);

    connect(ui->btnShow, SIGNAL(toggled(bool)), this, SLOT(showIssuesToggled(bool)));
    ui->expandWidget->hide();
}

DependencyCheckerWidget::~DependencyCheckerWidget()
{
    delete ui;
}

void DependencyCheckerWidget::setModManager(ModManager *currentMM)
{
    if(m_currentMM != nullptr)
    {
        disconnect(m_currentMM, SIGNAL(dependencyCheckFinished()), this, SLOT(updateData()));
    }

    m_currentMM = currentMM;

    if(m_currentMM != nullptr)
    {
        connect(m_currentMM, SIGNAL(dependencyCheckFinished()), this, SLOT(updateData()));
    }

    updateData();
}

void DependencyCheckerWidget::updateData()
{
    if(m_currentMM == nullptr)
    {
        hide();
        return;
    }

    QMap<QString, QList<Dependency>> issues = m_currentMM->getUnsatisfiedDependencies();

    if(issues.empty())
    {
        hide();
    }
    else
    {
        ui->lblIssues->setText("");
        show();

        ui->lblIssues->insertHtml("<p>Some mods might need other mods to run. Following dependencies could not be found:</p>\n");

        for(QString modid : issues.keys())
        {
            utils::moveTextCursorToEnd(ui->lblIssues);
            ui->lblIssues->insertHtml("<h4>" + modid + "</h4>\n");
        }
    }
}

void DependencyCheckerWidget::showIssuesToggled(bool toggle)
{
    ui->expandWidget->setVisible(toggle);
}
