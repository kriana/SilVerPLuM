#ifndef CATEGORYFILTERWIDGET_H
#define CATEGORYFILTERWIDGET_H

#include <QWidget>
#include <QComboBox>
#include "modification.h"

class CategoryComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit CategoryComboBox(QWidget *parent = 0);
    ~CategoryComboBox();

    void fillWith(const QList<Modification*> mods);

    QString currentCategory();

private:

private slots:

    void selectedEntry(int index);

signals:

    void selectedCategory(const QString & category);


};

#endif // CATEGORYFILTERWIDGET_H
