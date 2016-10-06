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

    void reloadModList();

private:
    Ui::ModManagerWidget *ui;

    ModManager * m_currentMM = nullptr;

private slots:

    void installModClicked();

    void search(const QString & searchstring_);
};

#endif // MODMANAGERWIDGET_H
