#include "modmanagerentrylist.h"
#include <QVBoxLayout>
#include "modmanagerwidgetitem.h"
#include "utils.h"

ModManagerEntryList::ModManagerEntryList(QWidget *parent) : QWidget(parent)
{
    this->setLayout(new QVBoxLayout(this));
    setAcceptDrops(true);
}

void ModManagerEntryList::setModManager(ModManager *currentMM)
{
    m_currentMM = currentMM;
}

void ModManagerEntryList::refreshList()
{
    utils::clearLayout(layout());

    QVBoxLayout * layout = dynamic_cast<QVBoxLayout*>(this->layout());

    if(m_currentMM != nullptr)
    {
        for(Modification * mod : m_currentMM->getModifications())
        {
            ModManagerWidgetItem * item = new ModManagerWidgetItem(this);
            item->setCurrentModification(mod);
            layout->addWidget(item);
        }
    }

    layout->addStretch(1);
}


void ModManagerEntryList::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->proposedAction() == Qt::MoveAction)
    {
        if(event->mimeData()->hasFormat("text/plain"))
        {
            QString modid = event->mimeData()->text();

            if(modid.endsWith("://"))
            {
                modid = modid.mid(0, modid.length() - 3);

                if(m_currentMM->getModification(modid) != nullptr)
                {
                    event->acceptProposedAction();
                }
            }
        }
    }
}

void ModManagerEntryList::dropEvent(QDropEvent *event)
{
    QString modid = event->mimeData()->text();
    modid = modid.mid(0, modid.length() - 3);

    Modification * mod = m_currentMM->getModification(modid);

    if(mod != nullptr)
    {       
        int index = matchReorderPosition(event->pos());

        //qDebug() << "Priotize to " << index;
        m_currentMM->priotizeTo(mod, index);
    }
}

void ModManagerEntryList::searchFilter(const QString &searchstring_, const QString & _filter)
{
    QString searchstring = searchstring_.trimmed();

    QLayout * layout = this->layout();

    for(int i = 0; i < layout->count(); ++i)
    {
        QLayoutItem * item = layout->itemAt(i);

        if(item->widget() != nullptr)
        {
            ModManagerWidgetItem * mitem = dynamic_cast<ModManagerWidgetItem*>(item->widget());

            if(mitem != nullptr)
            {
                mitem->searchFilter(searchstring, _filter);
            }
        }
    }
}

int ModManagerEntryList::matchReorderPosition(const QPoint &pos)
{
    QLayout * layout = this->layout();


    for(int i = 0; i < layout->count(); ++i)
    {
        QLayoutItem * item = layout->itemAt(i);

        if(item->widget() != nullptr)
        {
            ModManagerWidgetItem * mitem = dynamic_cast<ModManagerWidgetItem*>(item->widget());

            if(mitem != nullptr)
            {
                if(mitem->pos().y() + mitem->height() / 2 > pos.y()) //Reached an entry. Centroid of the entry decides if it's sorted before or after
                {
                    return i;
                }
            }
        }
    }

    return m_currentMM->getModifications().count();
}