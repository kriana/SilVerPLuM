#ifndef MODMANAGERENTRYLIST_H
#define MODMANAGERENTRYLIST_H

#include <QWidget>
#include "profilemanager.h"
#include "modmanager.h"

class ModManagerEntryList : public QWidget
{
    Q_OBJECT

public:
    ModManagerEntryList(QWidget * parent = nullptr);

public slots:

    void refreshList();

    void setModManager(ModManager *currentMM);

    void searchFilter(const QString &searchstring_, const QString & _filter);


private:

    ModManager * m_currentMM = nullptr;

    int matchReorderPosition(const QPoint & pos);

protected:

    void dragEnterEvent(QDragEnterEvent * event);

    void dropEvent(QDropEvent * event);
};

#endif // MODMANAGERENTRYLIST_H
