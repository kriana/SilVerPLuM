#include "modmanagerwidget.h"
#include "ui_modmanagerwidget.h"

ModManagerWidget::ModManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidget)
{
    ui->setupUi(this);
}

ModManagerWidget::~ModManagerWidget()
{
    delete ui;
}

Profile *ModManagerWidget::currentProfile() const
{
    return m_currentProfile;
}

void ModManagerWidget::setCurrentProfile(Profile *currentProfile)
{
    m_currentProfile = currentProfile;
}
