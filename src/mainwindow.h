#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "profile.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:

    void playClicked();

    void playSubActionTriggered();

    void cmbSelectedProfile(int index);

    void profileSelected(Profile * p);

    void profilesUpdated();

    void updateLauncherInfo();

    void gameRunning(bool running);

    void gameLog(const Logger::Entry &entry);

    void gameProgress(bool enabled, int _min, int _max, int _value);

    void closeLogClicked();

    void openApplicationSettings();

    void openProfileLog();

protected:

    void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H
