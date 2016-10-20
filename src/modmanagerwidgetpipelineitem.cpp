#include "modmanagerwidgetpipelineitem.h"
#include "ui_modmanagerwidgetpipelineitem.h"
#include "modification.h"
#include "modmanager.h"
#include "globalsettings.h"
#include <QMessageBox>
#include <QScrollBar>
#include "utils.h"
#include "logviewer.h"

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

        bool enabled;

        switch(m_currentPipeline->pipelineMainType())
        {
        case Pipeline::ContentPipeline:
            enabled = m_currentPipeline->isEnabled();
            ui->btnDisable->setVisible(enabled);
            ui->btnEnable->setVisible(!enabled);
            ui->btnRun->hide();
            break;
        case Pipeline::ProgramPipeline:
            enabled = true;
            ui->btnRun->show();
            ui->btnEnable->hide();
            ui->btnDisable->hide();
            break;
        }

        ui->lblIcon->setEnabled(enabled);

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
        enabled = m_currentPipeline->isEnabled();
        ui->btnDisable->setVisible(enabled);
        ui->btnEnable->setVisible(!enabled);
        ui->lblIcon->setEnabled(enabled);
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

        while(err != 0)
        {
            QMessageBox msg;
            msg.setText("Activating content");
            msg.setInformativeText("An error happened while activating the content. What do you want to do?");
            msg.setStandardButtons(QMessageBox::Ignore | QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Open);
            msg.setButtonText(QMessageBox::Abort, "Deactivate content");
            msg.setButtonText(QMessageBox::Open, "Open profile log");

            int action = msg.exec();

            if(action == QMessageBox::Ignore)
            {
                return;
            }
            else if(action == QMessageBox::Abort)
            {
                m_currentPipeline->setEnabled(false);
                return;
            }
            else if(action == QMessageBox::Retry)
            {
                m_currentPipeline->setEnabled(false);
                err = m_currentPipeline->setEnabled(true);
            }
            else if(action == QMessageBox::Open)
            {
                LogViewer::execForProfile(m_currentPipeline->mod()->getModManager()->profile());
            }
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
