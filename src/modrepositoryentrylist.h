#ifndef MODREPOSITORYENTRYLIST_H
#define MODREPOSITORYENTRYLIST_H

#include <QWidget>
#include <QList>
#include "modrepositoryentry.h"

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

private:
    Ui::ModRepositoryEntryList *ui;
};

#endif // MODREPOSITORYENTRYLIST_H
