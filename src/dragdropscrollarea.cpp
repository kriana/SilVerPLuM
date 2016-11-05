#include "dragdropscrollarea.h"
#include <QEvent>
#include <QDebug>
#include <QDragMoveEvent>
#include <QScrollBar>

DragDropScrollArea::DragDropScrollArea(QWidget *parent) : QScrollArea(parent)
{
    viewport()->installEventFilter(this);
    //viewport()->setAcceptDrops(true);

    m_scrollTimer = new QTimer(this);
    m_scrollTimer->setInterval(250);
    connect(m_scrollTimer, SIGNAL(timeout()), this, SLOT(triggerScroll()));
}

bool DragDropScrollArea::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::DragMove)
    {
        QDragMoveEvent * mv = dynamic_cast<QDragMoveEvent*>(event);

        if(mv != nullptr)
        {
            int pos = mv->pos().y() - verticalScrollBar()->value();

            //qDebug() << mv->pos().y() << "+" << verticalScrollBar()->value();
            //qDebug() << pos << m_scrollThreshold << height() - m_scrollThreshold;

            if(pos < m_scrollThreshold)
            {
                m_scrollToTop = true;
                m_scrollTimer->start();
            }
            else if(pos > height() - m_scrollThreshold)
            {
                m_scrollToTop = false;
                m_scrollTimer->start();
            }
            else
            {
                m_scrollTimer->stop();
            }
        }
    }
    else if(event->type() == QEvent::DragLeave)
    {
        m_scrollTimer->stop();
    }
    else if(event->type() == QEvent::Drop)
    {
        m_scrollTimer->stop();
    }

    return QScrollArea::eventFilter(target, event);
}

void DragDropScrollArea::triggerScroll()
{
    int value;

    if(m_scrollToTop)
    {
        value = verticalScrollBar()->value() - abs(verticalScrollBar()->pageStep());
    }
    else
    {
        value = verticalScrollBar()->value() + abs(verticalScrollBar()->pageStep());
    }

    //qDebug() << value;
    verticalScrollBar()->setValue(value);
}
