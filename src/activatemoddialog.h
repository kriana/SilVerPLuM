#ifndef ACTIVATEMODDIALOG_H
#define ACTIVATEMODDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QtConcurrent>
#include "modification.h"

namespace Ui {
class ActivateModDialog;
}

class ActivateModDialog : public QDialog
{
    Q_OBJECT

public:

    enum ActivateOperation
    {
        ReinitializeMod,
        ActivateMod,
        ActivatePipeline
    };

    explicit ActivateModDialog(QWidget *parent = 0);
    ~ActivateModDialog();

    void reininitializeModification(Modification * mod);

    void activateModification(Modification * mod);

    void activatePipeline(Pipeline * pip);

    bool isWorking() const;

protected:

    void closeEvent(QCloseEvent * event);

private:
    Ui::ActivateModDialog *ui;

    bool m_isWorking;

    ActivateOperation m_operation;

    QFutureWatcher<int> m_watcher;

    Modification * m_currentModification = nullptr;

    Pipeline * m_currentPipeline = nullptr;

    void setIsWorking(bool isWorking);

private slots:

    void finishedWorking();

    void runWorkload();

    void gotLog(const Logger::Entry &entry);
};

#endif // ACTIVATEMODDIALOG_H
