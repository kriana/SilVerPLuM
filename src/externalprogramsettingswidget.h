#ifndef EXTERNALPROGRAMSETTINGSWIDGET_H
#define EXTERNALPROGRAMSETTINGSWIDGET_H

#include <QWidget>
#include "globalsettings.h"

namespace Ui {
class ExternalProgramSettingsWidget;
}

class ExternalProgramSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExternalProgramSettingsWidget(QWidget *parent = 0);
    ~ExternalProgramSettingsWidget();

    ExternalProgram getExternalProgram();

    QString getExternalProgramId();

    void fillWith(const QString & programid);

signals:

    void changed();

private:
    Ui::ExternalProgramSettingsWidget *ui;

private slots:

    void removeEntry();

    void checkIfProgramExists();

    void addMimeType();
};

#endif // EXTERNALPROGRAMSETTINGSWIDGET_H
