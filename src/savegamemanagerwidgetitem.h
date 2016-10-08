#ifndef SAVEGAMEMANAGERWIDGETITEM_H
#define SAVEGAMEMANAGERWIDGETITEM_H

#include <QWidget>
#include "backupsavegame.h"

namespace Ui {
class SavegameManagerWidgetItem;
}

class SavegameManagerWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit SavegameManagerWidgetItem(QWidget *parent = 0);
    ~SavegameManagerWidgetItem();


    BackupSavegame *savegame() const;
    void setSavegame(BackupSavegame *savegame);

public slots:

    void updateData();

    void reloadList();

private:
    Ui::SavegameManagerWidgetItem *ui;

    BackupSavegame * m_savegame = nullptr;

private slots:

    void showMoreToggled(bool toggle);

    void savegameBackup();

    void savegameDelete();

    void savegameDeleteMain();

    void savegameCopyTo();

    void savegameSingle();

    void savegamePrune();
};

#endif // SAVEGAMEMANAGERWIDGETITEM_H
