#include "modmanagerwidgetpipelineitem.h"
#include "ui_modmanagerwidgetpipelineitem.h"
#include "modification.h"
#include "modmanager.h"
#include "globalsettings.h"
#include <QMessageBox>
#include <QScrollBar>
#include "utils.h"

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
       ui->lblDescription->setText(utils::makeTextEditHTML(utils::markdownToHTML(m_currentPipeline->mod()->getModManager()->autoResolveModUrls(m_currentPipeline->description()))));
        ui->lblIdentifier->setText(m_currentPipeline->id());

        bool enabled = m_currentPipeline->isEnabled();
        ui->btnDisable->setVisible(enabled);
        ui->btnEnable->setVisible(!enabled);

        // Set icon if available
        QString iconfilename = m_currentPipeline->pipelineBaseDir().absoluteFilePath("icon.png");
        QPixmap icon;

        if(!icon.load(iconfilename))
        {
            icon.load(":/resources/icons/module-100.png");
        }

        ui->lblIcon->setPixmap(icon);

        // Unsupported
        bool supported = !m_currentPipeline->unsupported() || GlobalSettings::instance()->getForceUnsupported();
        setEnabled(supported);
        ui->lblInfo->setText(supported ? "" : "This content is not supported on your platform.");

        // UI
        ui->lblDescription->verticalScrollBar()->setValue(ui->lblDescription->verticalScrollBar()->minimum());
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
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        int err = m_currentPipeline->setEnabled(true);

        QApplication::restoreOverrideCursor();

        if(err != 0)
        {
            QMessageBox::information(this, "Enable content", "Something went wrong while activating the modification. Open the 'Profile log' at 'Play' to see what happened.");
        }
    }
}

void ModManagerWidgetPipelineItem::disableClicked()
{
    if(m_currentPipeline != nullptr)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        m_currentPipeline->setEnabled(false);

        QApplication::restoreOverrideCursor();
    }
}
