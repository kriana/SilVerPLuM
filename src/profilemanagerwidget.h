#ifndef PROFILEMANAGERWIDGET_H
#define PROFILEMANAGERWIDGET_H

#include <QWidget>
#include "profilemanager.h"

namespace Ui {
class ProfileManagerWidget;
}

class ProfileManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileManagerWidget(QWidget *parent = 0);
    ~ProfileManagerWidget();

private slots:

    void selectedProfile(int index);

    void profileSelected(Profile * p);

    void profilesUpdated();

    void addProfileClicked();

    void duplicateProfileClicked();

    void removeProfileClicked();

    void exportProfileClicked();

    void importProfileClicked();

    void gameRunning(bool running);

private:
    Ui::ProfileManagerWidget *ui;

    bool m_loading = false;
};

#endif // PROFILEMANAGERWIDGET_H
