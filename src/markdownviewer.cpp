#include "markdownviewer.h"
#include "ui_markdownviewer.h"
#include "markdownviewerpage.h"
#include <QWebChannel>

MarkdownViewer::MarkdownViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkdownViewer)
{
    ui->setupUi(this);

    MarkdownViewerPage *page = new MarkdownViewerPage(this);
    ui->preview->setPage(page);

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &m_content);
    page->setWebChannel(channel);

    ui->preview->setUrl(QUrl("qrc:/resources/markdown/index.html"));
}

MarkdownViewer::~MarkdownViewer()
{
    delete ui;
}

void MarkdownViewer::setText(const QString &text)
{
    m_content.setText(text);
}
