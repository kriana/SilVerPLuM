#ifndef SAVEGAMEMANAGERWIDGETBACKUPITEM_H
#define SAVEGAMEMANAGERWIDGETBACKUPITEM_H

#include <QWidget>
#include "backupsavegame.h"

namespace Ui {
class SavegameManagerWidgetBackupItem;
}

class SavegameManagerWidgetBackupItem : public QWidget
{
    Q_OBJECT

public:
    explicit SavegameManagerWidgetBackupItem(QWidget *parent = 0);
    ~SavegameManagerWidgetBackupItem();

    Savegame *savegame() const;
    void setSavegame(BackupSavegame *parent, Savegame *savegame);

private slots:

    void savegameRestore();

    void savegameDelete();

    void savegameSingle();

private:
    Ui::SavegameManagerWidgetBackupItem *ui;

    Savegame * m_savegame = nullptr;

    BackupSavegame* m_parentSavegame = nullptr;
};

#endif // SAVEGAMEMANAGERWIDGETBACKUPITEM_H
