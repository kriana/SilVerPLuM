#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(QWidget *parent = 0);
    ~MessageWidget();

    void message(const QString & msg);

    void setText(const QString & text);

    QToolButton *getCloseButton();

    QPushButton * getActionButton();

private:
    Ui::MessageWidget *ui;


};

#endif // MESSAGEWIDGET_H
