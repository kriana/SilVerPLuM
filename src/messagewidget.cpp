#include "messagewidget.h"
#include "ui_messagewidget.h"
#include <QToolButton>
#include <QLabel>

MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);

    connect(ui->btnCloseMessage, SIGNAL(clicked(bool)), this, SLOT(hide()));
    hide();

    ui->btnAction->hide();

    // Build style
    QColor background_top = palette().color(QPalette::Active, QPalette::Highlight);
    QColor background_bottom = background_top.dark(120);
    QColor border = palette().color(QPalette::Active, QPalette::Shadow);

    ui->frame->setStyleSheet(QString("QFrame#frame {"
                                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 %1, stop:1 %2);"
                                    "border: 1px solid %3;"
                                    "border-radius: 3px;"
                                    "}").arg(background_top.name()).arg(background_bottom.name()).arg(border.name()));
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::message(const QString &msg)
{
    ui->lblMessage->setText(msg);
    show();
}

void MessageWidget::setText(const QString &text)
{
    ui->lblMessage->setText(text);
}

QToolButton *MessageWidget::getCloseButton()
{
    return ui->btnCloseMessage;
}

QPushButton *MessageWidget::getActionButton()
{
    return ui->btnAction;
}
