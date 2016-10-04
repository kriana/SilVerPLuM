#include "modmanagerwidgetitem.h"
#include "ui_modmanagerwidgetitem.h"

ModManagerWidgetItem::ModManagerWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidgetItem)
{
    ui->setupUi(this);
}

ModManagerWidgetItem::~ModManagerWidgetItem()
{
    delete ui;
}
