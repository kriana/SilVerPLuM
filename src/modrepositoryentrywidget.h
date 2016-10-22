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

    ModRepositoryEntry *currentEntry() const;

private:
    Ui::ModRepositoryEntryWidget *ui;

    bool m_updatesModification;

    ModRepositoryEntry * m_currentEntry = nullptr;

private slots:

    void installClicked();
};

#endif // MODREPOSITORYENTRYWIDGET_H
