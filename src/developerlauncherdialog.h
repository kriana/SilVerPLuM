#ifndef DEVELOPERLAUNCHERDIALOG_H
#define DEVELOPERLAUNCHERDIALOG_H

#include <QDialog>


namespace Ui {
class DeveloperLauncherDialog;
}

class Profile;

class DeveloperLauncherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeveloperLauncherDialog(QWidget *parent = 0);
    ~DeveloperLauncherDialog();

private:
    Ui::DeveloperLauncherDialog *ui;

    Profile * getProfile();

private slots:

    void showProfileLogClicked();

    void openFolderClicked();
};

#endif // DEVELOPERLAUNCHERDIALOG_H
