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

    explicit ActivateModDialog(QWidget *parent = 0);
    ~ActivateModDialog();

    int reininitializeModification(Modification * mod);

    int activateModification(Modification * mod);

    int activatePipeline(Pipeline * pip);

    bool isWorking() const;

protected:

    void closeEvent(QCloseEvent * event);

private:
    Ui::ActivateModDialog *ui;

    bool m_isWorking;

    bool m_reinitialize;

    QFutureWatcher<int> m_watcher;

    ModManager * m_modManager = nullptr;

    QList<Pipeline*> m_pipelinesToActivate;

    void setIsWorking(bool isWorking);

private slots:

    void finishedWorking();

    void runPreparation();

    void runWorkload();

    void gotLog(const Logger::Entry &entry);

    void dependencyActivateClicked();

    void dependencyIgnoreClicked();

    void activationIgnoreClicked();

    void activationRetryClicked();

    void activationCancelClicked();
};

#endif // ACTIVATEMODDIALOG_H
