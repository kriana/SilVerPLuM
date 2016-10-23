#include "dependencycheckerwidget.h"
#include "ui_dependencycheckerwidget.h"
#include "utils.h"
#include "globalsettings.h"
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
        disconnect(m_currentMM, SIGNAL(updatedModList()), this, SLOT(dependencyCheck()));
        disconnect(m_currentMM, SIGNAL(updatedModStatus(QString,QString,bool)), this, SLOT(dependencyCheck()));
    }

    m_currentMM = currentMM;

    if(m_currentMM != nullptr)
    {
        connect(m_currentMM, SIGNAL(updatedModList()), this, SLOT(dependencyCheck()));
        connect(m_currentMM, SIGNAL(updatedModStatus(QString,QString,bool)), this, SLOT(dependencyCheck()));
    }

    dependencyCheck();
}

void DependencyCheckerWidget::dependencyCheck()
{
    if(m_currentMM == nullptr || !GlobalSettings::instance()->getEnableDepencencyCheck())
    {
        hide();
        return;
    }

    bool found = false;
    QString html;

    html += "<html><body>";

    for(Modification * mod : m_currentMM->getModifications())
    {
        if(!mod->isPartiallyEnabled())
            continue;

        DependencyTree::DependencyCheckResult result = m_currentMM->getDependencyTree()->dependenciesFulfilled(mod,
                                                                                                               GlobalSettings::instance()->getEnableDepencyCheckPriorityAwareness(),
                                                                                                               false);
        if(!result.satisfied())
        {
            found = true;

            html += "<h4>" + mod->name() + " (" + mod->id() + ")" + "</h4>";

            QList<Modification*> deactivated_missing;
            QList<Modification*> wrong_ordered_missing;

            for(Modification * m : result.missing)
            {
                if(m->isPartiallyEnabled())
                    wrong_ordered_missing << m;
                else
                    deactivated_missing << m;
            }

            if(!deactivated_missing.isEmpty())
            {
                html += "<h5>Need to be activated</h5>";

                html += "<ul>";

                for(Modification * m : deactivated_missing)
                {
                    html += QString("<li>%1 (%2)</li>").arg(m->name()).arg(m->id());
                }

                html += "</ul>";
            }

            if(!wrong_ordered_missing.isEmpty())
            {
                html += "<h5>Need to be sorted to the top</h5>";

                html += "<ul>";

                for(Modification * m : wrong_ordered_missing)
                {
                    html += QString("<li>%1 (%2)</li>").arg(m->name()).arg(m->id());
                }

                html += "</ul>";
            }

            if(!result.unresolved.isEmpty())
            {
                html += "<h5>Missing dependencies</h5>";

                html += "<ul>";

                for(Dependency dep : result.unresolved)
                {
                    html += QString("<li>%1</li>").arg(dep.toPrettyString());
                }


                html += "</ul>";
            }
        }
    }

    html += "</body></html>";

    ui->lblIssues->document()->setHtml(html);

    setVisible(found);

    /*QMap<QString, QList<Dependency>> issues = m_currentMM->getUnsatisfiedDependencies();

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


    }*/
}

void DependencyCheckerWidget::showIssuesToggled(bool toggle)
{
    ui->expandWidget->setVisible(toggle);
}
