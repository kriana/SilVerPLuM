#include "modmanagerwidgetpipelineitem.h"
#include "ui_modmanagerwidgetpipelineitem.h"
#include "modification.h"
#include "modmanager.h"
#include "globalsettings.h"

ModManagerWidgetPipelineItem::ModManagerWidgetPipelineItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidgetPipelineItem)
{
    ui->setupUi(this);

    connect(ui->btnEnable, &QPushButton::clicked, this,&ModManagerWidgetPipelineItem::enableClicked);
    connect(ui->btnDisable, &QPushButton::clicked, this, &ModManagerWidgetPipelineItem::disableClicked);
}

ModManagerWidgetPipelineItem::~ModManagerWidgetPipelineItem()
{
    delete ui;
}

Pipeline *ModManagerWidgetPipelineItem::currentPipeline() const
{
    return m_currentPipeline;
}

void ModManagerWidgetPipelineItem::setCurrentPipeline(Pipeline *currentPipeline)
{
    if(m_currentPipeline != nullptr)
    {
        disconnect(m_currentPipeline,
                   SIGNAL(contentEnabledDisabled(bool)),
                   this,
                   SLOT(contentEnabledDisabled(bool)));
    }

    m_currentPipeline = currentPipeline;

    if(m_currentPipeline != nullptr)
    {
        connect(m_currentPipeline,
                   SIGNAL(contentEnabledDisabled(bool)),
                   this,
                   SLOT(contentEnabledDisabled(bool)));

        ui->lblName->setText(m_currentPipeline->name());
        ui->lblDescription->setText(m_currentPipeline->description());
        ui->lblIdentifier->setText(m_currentPipeline->id());

        bool enabled = m_currentPipeline->isEnabled();
        ui->btnDisable->setVisible(enabled);
        ui->btnEnable->setVisible(!enabled);

        // Set icon if available
        QString iconfilename = m_currentPipeline->profileBaseDir().absoluteFilePath("icon.png");
        QPixmap icon;

        if(!icon.load(iconfilename))
        {
            icon.load(":/resources/icons/module-100.png");
        }

        ui->lblIcon->setPixmap(icon);

        // Unsupported
        setEnabled(!m_currentPipeline->unsupported() || GlobalSettings::instance()->getForceUnsupported());
    }
}

void ModManagerWidgetPipelineItem::contentEnabledDisabled(bool enabled)
{
    if(m_currentPipeline != nullptr)
    {
        bool enabled = m_currentPipeline->isEnabled();
        ui->btnDisable->setVisible(enabled);
        ui->btnEnable->setVisible(!enabled);
    }
}

void ModManagerWidgetPipelineItem::enableClicked()
{
    if(m_currentPipeline != nullptr)
    {
        m_currentPipeline->setEnabled(true);
    }
}

void ModManagerWidgetPipelineItem::disableClicked()
{
    if(m_currentPipeline != nullptr)
    {
        m_currentPipeline->setEnabled(false);
    }
}
