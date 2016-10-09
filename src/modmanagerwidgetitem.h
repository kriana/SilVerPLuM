#ifndef MODMANAGERWIDGETITEM_H
#define MODMANAGERWIDGETITEM_H

#include <QWidget>
#include "modification.h"

namespace Ui {
class ModManagerWidgetItem;
}

class ModManagerWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit ModManagerWidgetItem(QWidget *parent = 0);
    ~ModManagerWidgetItem();

    void setCurrentModification(Modification * mod);

    void setCollapsed(bool enabled);

    void search(const QString & searchstring);

private slots:

    void showMoreToggled(bool toggle);

    void contentEnabledDisabled(const QString & contentid, bool enabled);

    void enableClicked();

    void disableClicked();

    void moveUpClicked();

    void moveDownClicked();

    void deleteClicked();

    void copyToProfileClicked();

    void reprimeClicked();

private:
    Ui::ModManagerWidgetItem *ui;

    Modification * m_currentModification = nullptr;

    void updateData();
};

#endif // MODMANAGERWIDGETITEM_H
