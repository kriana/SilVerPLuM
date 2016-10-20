#ifndef MODREPOSITORY_H
#define MODREPOSITORY_H

#include <QObject>

class ModManager;

class ModRepository : public QObject
{
    Q_OBJECT
public:
    ModRepository(ModManager * mgr);

    /**
     * @brief Returns true if the repository needs an update
     * @return
     */
    bool needsUpdate() const;

signals:

    void repositoryNeedsUpdate();

public slots:

    void triggerNeedsUpdate();

private:

    bool m_needsUpdate;
};

#endif // MODREPOSITORY_H
