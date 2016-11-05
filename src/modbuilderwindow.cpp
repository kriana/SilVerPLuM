#include "modbuilderwindow.h"
#include "ui_modbuilderwindow.h"

ModBuilderWindow::ModBuilderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModBuilderWindow)
{
    ui->setupUi(this);
}

ModBuilderWindow::~ModBuilderWindow()
{
    delete ui;
}
