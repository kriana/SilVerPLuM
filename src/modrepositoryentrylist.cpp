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
    m_currentListEntries.clear();

    for(ModRepositoryEntry * entry : entries)
    {
        ModRepositoryEntryWidget * wdg = new ModRepositoryEntryWidget(ui->scrollAreaWidgetContents);
        wdg->setRepositoryEntry(entry);

        layout->addWidget(wdg);
        m_currentListEntries << wdg;
    }

    layout->addStretch(1);
    applySearch();

    ui->scrollArea->verticalScrollBar()->setValue(scroll);
}

void ModRepositoryEntryList::search(const QString &searchstring)
{
    m_searchString = searchstring;
    applySearch();
}

void ModRepositoryEntryList::filterCategory(const QString &category)
{
    m_filterCategory = category;

    applySearch();
}

void ModRepositoryEntryList::searchFilter(const QString & searchstring, const QString & category)
{
    m_searchString = searchstring;
    m_filterCategory = category;

    applySearch();
}

void ModRepositoryEntryList::applySearch()
{
    QString search = m_searchString.toLower().trimmed();

    for(ModRepositoryEntryWidget * wdg : m_currentListEntries)
    {
        if(wdg->currentEntry()->searchFilter(search, m_filterCategory))
            wdg->show();
        else
            wdg->hide();
    }
}
