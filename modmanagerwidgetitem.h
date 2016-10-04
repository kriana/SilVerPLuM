#ifndef MODMANAGERWIDGETITEM_H
#define MODMANAGERWIDGETITEM_H

#include <QWidget>

namespace Ui {
class ModManagerWidgetItem;
}

class ModManagerWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit ModManagerWidgetItem(QWidget *parent = 0);
    ~ModManagerWidgetItem();

private:
    Ui::ModManagerWidgetItem *ui;
};

#endif // MODMANAGERWIDGETITEM_H
