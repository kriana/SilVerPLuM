#include "logviewer.h"
#include "ui_logviewer.h"
#include "utils.h"
#include "profilemanager.h"
#include <QClipboard>

LogViewer::LogViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogViewer)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);

    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btnCopy, SIGNAL(clicked(bool)), this, SLOT(copyClicked()));
}

LogViewer::~LogViewer()
{
    delete ui;
}

void LogViewer::setLogger(const Logger &logger)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    QString html = "<table>";
    m_logText = "";

    html += "<tr><th>Type</th><th>Timestamp</th><th>Component</th><th>Subcomponent</th><th>Operation</th><th>Message</th></tr>";

    for(const Logger::Entry & entry : logger.entries())
    {
        html += formatEntry(entry);
        m_logText += entry.toString() + "\n";
    }

    html += "</table>";

    ui->lblLog->setHtml(utils::makeTextEditHTML(html));
    ui->lblLog->verticalScrollBar()->setValue(ui->lblLog->verticalScrollBar()->maximum());

    QApplication::restoreOverrideCursor();
}

void LogViewer::execForProfile(Profile *p)
{
    Logger joined;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    joined.insert(p->getLogger());
    //joined.insert(p->getModManager()->getLogger());
    joined.insert(ProfileManager::instance()->getLogger());

    for(Modification * mod : p->getModManager()->getModifications())
    {
        joined.insert(mod->getLogger());
    }

    QApplication::restoreOverrideCursor();

    LogViewer dlg;
    dlg.setWindowTitle(QString("Logviewer for profile %1 (%2)").arg(p->name()).arg(p->id()));
    dlg.setLogger(joined);
    dlg.exec();
}

void LogViewer::copyClicked()
{
    QApplication::clipboard()->setText(m_logText);
}

QString LogViewer::formatEntry(const Logger::Entry &entry)
{
    QString msg = entry.message;

    return QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td></tr>")
            .arg(entry.levelToString())
            .arg(entry.timestamp.toString())
            .arg(entry.component)
            .arg(entry.subcomponent)
            .arg(entry.operation)
            .arg(msg.replace("\n", "<br/>"));
}
