#include "categoryfilterwidget.h"
#include "ui_categoryfilterwidget.h"
#include <QComboBox>

CategoryFilterWidget::CategoryFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryFilterWidget)
{
    ui->setupUi(this);

    ui->categoryList->addItem(tr("No category"), "");

    connect(ui->categoryList, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedEntry(int)));
}

CategoryFilterWidget::~CategoryFilterWidget()
{
    delete ui;
}

void CategoryFilterWidget::fillWith(const QList<Modification *> mods)
{
    ui->categoryList->clear();
    ui->categoryList->addItem(tr("No category"), "");

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
        ui->categoryList->addItem(cat, cat.toLower());
    }

    selectedEntry(ui->categoryList->currentIndex());
}

QString CategoryFilterWidget::currentCategory()
{
    return ui->categoryList->currentData().toString();
}

void CategoryFilterWidget::selectedEntry(int index)
{
    if(index >= 0)
    {
        emit selectedCategory(ui->categoryList->itemData(index).toString());
    }
}
