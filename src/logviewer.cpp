#include "logviewer.h"
#include "ui_logviewer.h"
#include "utils.h"

LogViewer::LogViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogViewer)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(close()));
}

LogViewer::~LogViewer()
{
    delete ui;
}

void LogViewer::setLogger(const Logger &logger)
{
    QString html = "<table>";

    html += "<tr><th>Type</th><th>Timestamp</th><th>Component</th><th>Subcomponent</th><th>Operation</th><th>Message</th></tr>";

    for(const Logger::Entry & entry : logger.entries())
    {
        html += formatEntry(entry);
    }

    html += "</table>";

    ui->lblLog->setHtml(utils::makeTextEditHTML(html));
}

void LogViewer::execForProfile(Profile *p)
{
    Logger joined;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    joined.insert(p->getLogger());
    joined.insert(p->getModManager()->getLogger());

    for(Modification * mod : p->getModManager()->getModifications())
    {
        joined.insert(mod->getLogger());

        for(Pipeline * pip : mod->getPipelines())
        {
            joined.insert(pip->getLogger());
        }
    }

    QApplication::restoreOverrideCursor();

    LogViewer dlg;
    dlg.setWindowTitle(QString("Logviewer for profile %1 (%2)").arg(p->name()).arg(p->id()));
    dlg.setLogger(joined);
    dlg.exec();
}

QString LogViewer::formatEntry(const Logger::Entry &entry)
{
    return QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td></tr>")
            .arg(entry.levelToString())
            .arg(entry.timestamp.toString())
            .arg(entry.component)
            .arg(entry.subcomponent)
            .arg(entry.operation)
            .arg(entry.message);
}
