#ifndef MODBUILDERWINDOW_H
#define MODBUILDERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ModBuilderWindow;
}

class ModBuilderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModBuilderWindow(QWidget *parent = 0);
    ~ModBuilderWindow();

private:
    Ui::ModBuilderWindow *ui;
};

#endif // MODBUILDERWINDOW_H
