#ifndef MARKDOWNVIEWERPAGE_H
#define MARKDOWNVIEWERPAGE_H

#include <QWebEnginePage>

class MarkdownViewerPage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit MarkdownViewerPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
};
#endif // MARKDOWNVIEWERPAGE_H
