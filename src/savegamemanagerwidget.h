#ifndef SAVEGAMEMANAGERWIDGET_H
#define SAVEGAMEMANAGERWIDGET_H

#include <QWidget>

#include "savegamemanager.h"
#include "profile.h"

namespace Ui {
class SavegameManagerWidget;
}

class SavegameManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SavegameManagerWidget(QWidget *parent = 0);
    ~SavegameManagerWidget();

    SavegameManager *savegameManager() const;

    void setSavegameManager(SavegameManager *savegameManager);

public slots:

    void reloadList();

    void reloadAllSavegames();

private:
    Ui::SavegameManagerWidget *ui;

    SavegameManager * m_savegameManager = nullptr;

private slots:

    void importSavegame();

    void gameRunning(bool running);
};

#endif // SAVEGAMEMANAGERWIDGET_H
