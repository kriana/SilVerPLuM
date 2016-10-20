#ifndef PIPELINELISTWIDGET_H
#define PIPELINELISTWIDGET_H

#include <QWidget>
#include "modmanagerwidgetpipelineitem.h"

namespace Ui {
class PipelineListWidget;
}

class PipelineListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PipelineListWidget(QWidget *parent = 0);
    ~PipelineListWidget();

    void setPipelines(QList<Pipeline*> pipelines);

private:
    Ui::PipelineListWidget *ui;
};

#endif // PIPELINELISTWIDGET_H
