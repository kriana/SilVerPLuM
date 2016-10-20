#ifndef MODREPOSITORYWINDOW_H
#define MODREPOSITORYWINDOW_H

#include <QDialog>

namespace Ui {
class ModRepositoryWindow;
}

class ModRepositoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModRepositoryWindow(QWidget *parent = 0);
    ~ModRepositoryWindow();

private:
    Ui::ModRepositoryWindow *ui;
};

#endif // MODREPOSITORYWINDOW_H
