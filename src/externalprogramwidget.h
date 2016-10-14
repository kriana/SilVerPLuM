#ifndef EXTERNALPROGRAMWIDGET_H
#define EXTERNALPROGRAMWIDGET_H

#include <QWidget>
#include "globalsettings.h"
#include "ui_externalprogramwidget.h"

namespace Ui {
class ExternalProgramWidget;
}

class ExternalProgramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExternalProgramWidget(QWidget *parent = 0);
    ~ExternalProgramWidget();

    ExternalProgram getExternalProgram();

    QString getExternalProgramId();

    void fillWith(const QString & programid);

signals:

    void changed();

private:
    Ui::ExternalProgramWidget *ui;

private slots:

    void removeEntry();

    void checkIfProgramExists();
};

#endif // EXTERNALPROGRAMWIDGET_H
