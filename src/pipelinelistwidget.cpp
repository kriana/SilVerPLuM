#include "pipelinelistwidget.h"
#include "ui_pipelinelistwidget.h"
#include "utils.h"

PipelineListWidget::PipelineListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PipelineListWidget)
{
    ui->setupUi(this);
}

PipelineListWidget::~PipelineListWidget()
{
    delete ui;
}

void PipelineListWidget::setPipelines(QList<Pipeline *> pipelines)
{
    // Add pipelines
    utils::clearLayout(ui->pipelineList->layout());
    bool first = true;
    for(Pipeline * pip : pipelines)
    {
        if(!first)
        {
            QFrame * hline = new QFrame(ui->pipelineList);
            hline->setFrameShadow(QFrame::Sunken);
            hline->setFrameShape(QFrame::HLine);
            ui->pipelineList->layout()->addWidget(hline);
        }
        else
        {
            first = false;
        }

        ModManagerWidgetPipelineItem * widget = new ModManagerWidgetPipelineItem(ui->pipelineList);
        widget->setCurrentPipeline(pip);
        widget->setMinimumHeight(230);

        ui->pipelineList->layout()->addWidget(widget);
    }
}
