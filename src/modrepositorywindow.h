#ifndef MODREPOSITORYWINDOW_H
#define MODREPOSITORYWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include "modrepository.h"

namespace Ui {
class ModRepositoryWindow;
}

class ModRepositoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModRepositoryWindow(QWidget *parent = 0);
    ~ModRepositoryWindow();

    ModRepository * getModRepository();

protected:

    void closeEvent(QCloseEvent * event);

private slots:

    void cancelClicked();

    void updateRepositoryClicked();

    void gotLog(const Logger::Entry &entry);

    void refreshList();

private:
    Ui::ModRepositoryWindow *ui;

    void updatePipelineList();
};

#endif // MODREPOSITORYWINDOW_H
