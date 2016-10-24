#ifndef MODREPOSITORYENTRYLIST_H
#define MODREPOSITORYENTRYLIST_H

#include <QWidget>
#include <QList>
#include "modrepositoryentry.h"
#include "modrepositoryentrywidget.h"

namespace Ui {
class ModRepositoryEntryList;
}

class ModRepositoryEntryList : public QWidget
{
    Q_OBJECT

public:
    explicit ModRepositoryEntryList(QWidget *parent = 0);
    ~ModRepositoryEntryList();

    void setEntryList(QList<ModRepositoryEntry*> entries);


public slots:

    void search(const QString & searchstring);

    void filterCategory(const QString & category);

    void searchFilter(const QString & searchstring, const QString & category);

private:
    Ui::ModRepositoryEntryList *ui;

    QList<ModRepositoryEntryWidget*> m_currentListEntries;

    QString m_searchString;

    QString m_filterCategory;

    void applySearch();
};

#endif // MODREPOSITORYENTRYLIST_H
