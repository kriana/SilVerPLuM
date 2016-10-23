#ifndef DEPENDENCYCHECKERWIDGET_H
#define DEPENDENCYCHECKERWIDGET_H

#include <QWidget>
#include "profile.h"

namespace Ui {
class DependencyCheckerWidget;
}

class DependencyCheckerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DependencyCheckerWidget(QWidget *parent = 0);
    ~DependencyCheckerWidget();

    void setModManager(ModManager *currentMM);

public slots:

    void dependencyCheck();

private:
    Ui::DependencyCheckerWidget *ui;

    ModManager * m_currentMM = nullptr;

private slots:

    void showIssuesToggled(bool toggle);
};

#endif // DEPENDENCYCHECKERWIDGET_H
