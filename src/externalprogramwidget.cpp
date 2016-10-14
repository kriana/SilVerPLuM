#include "externalprogramwidget.h"
#include "ui_externalprogramwidget.h"

ExternalProgramWidget::ExternalProgramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExternalProgramWidget)
{
    ui->setupUi(this);
}

ExternalProgramWidget::~ExternalProgramWidget()
{
    delete ui;
}
