#ifndef MODREPOSITORY_H
#define MODREPOSITORY_H

#include <QObject>

class ModManager;

class ModRepository : public QObject
{
    Q_OBJECT
public:
    ModRepository(ModManager * mgr);

signals:

public slots:
};

#endif // MODREPOSITORY_H
