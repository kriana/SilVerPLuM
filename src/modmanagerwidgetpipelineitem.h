#ifndef MODMANAGERWIDGETPIPELINEITEM_H
#define MODMANAGERWIDGETPIPELINEITEM_H

#include <QWidget>
#include "pipeline.h"

namespace Ui {
class ModManagerWidgetPipelineItem;
}

class ModManagerWidgetPipelineItem : public QWidget
{
    Q_OBJECT

public:
    explicit ModManagerWidgetPipelineItem(QWidget *parent = 0);
    ~ModManagerWidgetPipelineItem();

    Pipeline *currentPipeline() const;
    void setCurrentPipeline(Pipeline *currentPipeline);

private:
    Ui::ModManagerWidgetPipelineItem *ui;

    Pipeline * m_currentPipeline = nullptr;

private slots:

    void contentEnabledDisabled(bool enabled);

    void enableClicked();

    void disableClicked();

    void runClicked();
};

#endif // MODMANAGERWIDGETPIPELINEITEM_H
