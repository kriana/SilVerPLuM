#ifndef GLOBALSETTINGSDIALOG_H
#define GLOBALSETTINGSDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class GlobalSettingsDialog;
}

class GlobalSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalSettingsDialog(QWidget *parent = 0);
    ~GlobalSettingsDialog();

public slots:

    void discart();

    void save();

    void saveOrDiscart(QAbstractButton * button);

private:
    Ui::GlobalSettingsDialog *ui;
};

#endif // GLOBALSETTINGSDIALOG_H
