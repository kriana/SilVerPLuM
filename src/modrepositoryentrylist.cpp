#include "modrepositoryentrylist.h"
#include "ui_modrepositoryentrylist.h"
#include "utils.h"
#include "modrepositoryentrywidget.h"
#include <QScrollBar>

ModRepositoryEntryList::ModRepositoryEntryList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModRepositoryEntryList)
{
    ui->setupUi(this);
}

ModRepositoryEntryList::~ModRepositoryEntryList()
{
    delete ui;
}

void ModRepositoryEntryList::setEntryList(QList<ModRepositoryEntry *> entries)
{
    int scroll = ui->scrollArea->verticalScrollBar()->value();

    std::sort(entries.begin(), entries.end(), [](ModRepositoryEntry * a, ModRepositoryEntry * b) {
       return a->modification()->name() < b->modification()->name();
    });

    QVBoxLayout * layout = dynamic_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    utils::clearLayout(layout);

    for(ModRepositoryEntry * entry : entries)
    {
        ModRepositoryEntryWidget * wdg = new ModRepositoryEntryWidget(ui->scrollAreaWidgetContents);
        wdg->setRepositoryEntry(entry);

        layout->addWidget(wdg);
    }

    layout->addStretch(1);

    ui->scrollArea->verticalScrollBar()->setValue(scroll);
}

void ModRepositoryEntryList::search(const QString &searchstring)
{

}
