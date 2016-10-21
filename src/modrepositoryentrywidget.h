#ifndef MODREPOSITORYENTRYWIDGET_H
#define MODREPOSITORYENTRYWIDGET_H

#include <QWidget>
#include "modrepositoryentry.h"

namespace Ui {
class ModRepositoryEntryWidget;
}

class ModRepositoryEntryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModRepositoryEntryWidget(QWidget *parent = 0);
    ~ModRepositoryEntryWidget();

    void setRepositoryEntry(ModRepositoryEntry * entry);

private:
    Ui::ModRepositoryEntryWidget *ui;

    ModRepositoryEntry * m_currentEntry = nullptr;
};

#endif // MODREPOSITORYENTRYWIDGET_H
