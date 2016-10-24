#ifndef MODMANAGERWIDGET_H
#define MODMANAGERWIDGET_H

#include <QWidget>
#include "profilemanager.h"
#include "modmanager.h"

namespace Ui {
class ModManagerWidget;
}

class ModManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModManagerWidget(QWidget *parent = 0);
    ~ModManagerWidget();

    ModManager *currentModManager() const;

public slots:

    void setModManager(ModManager *currentMM);

    void refreshList();

    void reloadAllMods();

private:
    Ui::ModManagerWidget *ui;

    ModManager * m_currentMM = nullptr;

    void searchFilter(const QString &searchstring_, const QString & _filter);

private slots:

    void addDefaultModsClicked();

    void importModClicked();

    void installModClicked();

    void repositoryClicked();

    void triggerSearchFilter();
};

#endif // MODMANAGERWIDGET_H
