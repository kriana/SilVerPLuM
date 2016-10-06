#include "dependencycheckerwidget.h"
#include "ui_dependencycheckerwidget.h"
#include "utils.h"
#include <QStringBuilder>

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
        QString html;

        html += "<html><body>";
        html += "<p>Some mods might need other mods to run. Following dependencies could not be found:</p>";

        for(QString modid : issues.keys())
        {
            Modification * mod = m_currentMM->getModification(modid);

            html += "<h4>" + mod->name() + " (" + modid + ")" + "</h4>";
            html += "<ul>";

            for(const Dependency & dep : issues[modid])
            {
                html += "<li>" + dep.toPrettyString() + "</li>";
            }

            html += "</ul>";
        }

        html += "</body></html>";

        ui->lblIssues->document()->setHtml(html);

        show();


    }
}

void DependencyCheckerWidget::showIssuesToggled(bool toggle)
{
    ui->expandWidget->setVisible(toggle);
}
