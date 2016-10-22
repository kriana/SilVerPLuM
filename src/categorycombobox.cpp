#include "categorycombobox.h"
#include <QComboBox>

CategoryComboBox::CategoryComboBox(QWidget *parent) :
    QComboBox(parent)
{
    addItem(tr("All categories"), "");
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedEntry(int)));
}

CategoryComboBox::~CategoryComboBox()
{
}

void CategoryComboBox::fillWith(const QList<Modification *> mods)
{
    clear();
    addItem(tr("All categories"), "");

    QStringList knowncategories;
    QStringList categories;

    for(Modification * mod : mods)
    {
        for(QString cat : mod->getCategories())
        {
            if(!knowncategories.contains(cat.toLower()))
            {
                knowncategories << cat.toLower();
                categories << cat;
            }
        }
    }

    std::sort(categories.begin(), categories.end());

    for(QString cat : categories)
    {
        addItem(cat, cat.toLower());
    }

    selectedEntry(currentIndex());
}

QString CategoryComboBox::currentCategory()
{
    return currentData().toString();
}

void CategoryComboBox::selectedEntry(int index)
{
    if(index >= 0)
    {
        emit selectedCategory(itemData(index).toString());
    }
}
