#include "modrepositorywindow.h"
#include "ui_modrepositorywindow.h"
#include <QPushButton>
#include <QTabWidget>

ModRepositoryWindow::ModRepositoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModRepositoryWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
    ui->tabWidget->setCurrentWidget(ui->tabWelcome);

    connect(ui->btnOverviewDownload, &QPushButton::clicked, this, [&]() {
       ui->tabWidget->setCurrentWidget(ui->tabDownload);
    });
    connect(ui->btnOverviewConfigure, &QPushButton::clicked, this, [&]() {
       ui->tabWidget->setCurrentWidget(ui->tabRepositories);
    });
    connect(ui->btnOverviewUpdate, &QPushButton::clicked, this, [&]() {
       ui->tabWidget->setCurrentWidget(ui->tabUpdate);
    });
}

ModRepositoryWindow::~ModRepositoryWindow()
{
    delete ui;
}
