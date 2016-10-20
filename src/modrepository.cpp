#include "modrepository.h"
#include "modmanager.h"

ModRepository::ModRepository(ModManager *mgr) : QObject(mgr)
{
    triggerNeedsUpdate();

    connect(mgr, SIGNAL(updatedModList()), this, SLOT(triggerNeedsUpdate()));
    connect(mgr, SIGNAL(updatedModStatus(QString,QString,bool)), this, SLOT(triggerNeedsUpdate()));
}

bool ModRepository::needsUpdate() const
{
    return m_needsUpdate;
}

void ModRepository::triggerNeedsUpdate()
{
    m_needsUpdate = true;
    emit repositoryNeedsUpdate();
}
