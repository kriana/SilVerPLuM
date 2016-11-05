#ifndef SCROLLINGSCROLLAREA_H
#define SCROLLINGSCROLLAREA_H

#include <QScrollArea>
#include <QTimer>

class DragDropScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit DragDropScrollArea(QWidget *parent = 0);

signals:

public slots:

protected:

    bool eventFilter(QObject * target, QEvent * event);

private:

    int m_scrollThreshold = 50;

    QTimer *m_scrollTimer;
    bool m_scrollToTop;

private slots:

    void triggerScroll();

};

#endif // SCROLLINGSCROLLAREA_H
