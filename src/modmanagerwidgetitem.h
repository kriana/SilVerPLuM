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

    void searchFilter(const QString & searchstring, const QString & category);

    Modification *currentModification() const;

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

    void exportClicked();

    void openDirectoryClicked();

protected:

    void mousePressEvent(QMouseEvent * event);

    void mouseMoveEvent(QMouseEvent * event);

private:
    Ui::ModManagerWidgetItem *ui;

    Modification * m_currentModification = nullptr;

    QPoint m_dragStartPosition;

    void updateData();
};

#endif // MODMANAGERWIDGETITEM_H
