#ifndef EXTERNALPROGRAMWIDGET_H
#define EXTERNALPROGRAMWIDGET_H

#include <QWidget>

namespace Ui {
class ExternalProgramWidget;
}

class ExternalProgramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExternalProgramWidget(QWidget *parent = 0);
    ~ExternalProgramWidget();

private:
    Ui::ExternalProgramWidget *ui;
};

#endif // EXTERNALPROGRAMWIDGET_H
