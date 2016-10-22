#ifndef CATEGORYFILTERWIDGET_H
#define CATEGORYFILTERWIDGET_H

#include <QWidget>
#include "modification.h"

namespace Ui {
class CategoryFilterWidget;
}

class CategoryFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryFilterWidget(QWidget *parent = 0);
    ~CategoryFilterWidget();

    void fillWith(const QList<Modification*> mods);

    QString currentCategory();

private:
    Ui::CategoryFilterWidget *ui;

private slots:

    void selectedEntry(int index);

signals:

    void selectedCategory(const QString & category);


};

#endif // CATEGORYFILTERWIDGET_H
