#ifndef MODMANAGERWIDGET_H
#define MODMANAGERWIDGET_H

#include <QWidget>
#include "profilemanager.h"

namespace Ui {
class ModManagerWidget;
}

class ModManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModManagerWidget(QWidget *parent = 0);
    ~ModManagerWidget();

    Profile *currentProfile() const;

public slots:

    void setCurrentProfile(Profile *currentProfile);

private:
    Ui::ModManagerWidget *ui;

    Profile * m_currentProfile;
};

#endif // MODMANAGERWIDGET_H
