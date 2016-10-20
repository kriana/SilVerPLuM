#ifndef MODREPOSITORYWINDOW_H
#define MODREPOSITORYWINDOW_H

#include <QDialog>
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

private slots:

    void updateRepositoryClicked();

private:
    Ui::ModRepositoryWindow *ui;

    void updatePipelineList();
};

#endif // MODREPOSITORYWINDOW_H
