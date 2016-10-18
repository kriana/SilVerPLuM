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
