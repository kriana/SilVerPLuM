#ifndef MARKDOWNVIEWER_H
#define MARKDOWNVIEWER_H

#include <QWidget>
#include "markdowndocument.h"

namespace Ui {
class MarkdownViewer;
}

class MarkdownViewer : public QWidget
{
    Q_OBJECT

public:
    explicit MarkdownViewer(QWidget *parent = 0);
    ~MarkdownViewer();

    void setText(const QString & text);

private:
    Ui::MarkdownViewer *ui;

    MarkdownDocument m_content;
};

#endif // MARKDOWNVIEWER_H
