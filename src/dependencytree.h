#ifndef DEPENDENCYTREE_H
#define DEPENDENCYTREE_H

#include "modification.h"

class  ModManager;

class DependencyTree : public QObject
{
    Q_OBJECT

public:

    struct TreeNode
    {
        Modification * modification;
        QList<Dependency> unresolved;
        QList<Modification*> dependencies;
    };

    struct DependencyCheckResult
    {
        QList<Modification*> missing;
        QList<Dependency> unresolved;

        bool satisfied()
        {
            return missing.isEmpty() && unresolved.isEmpty();
        }
    };

    DependencyTree(ModManager * mgr);

    ~DependencyTree();

    bool resolveMetaDependency(const Dependency & dep);

    Modification * resolveDependency(const Dependency & dep);

    DependencyCheckResult dependenciesFulfilled(Modification * rootmod, bool priorityaware, bool complete);

public slots:

    void rebuildTree();

private:

    ModManager * m_modManager;
    QList<TreeNode*> m_nodes;
    QMap<Modification*, TreeNode*> m_modNodes;
};

#endif // DEPENDENCYTREE_H
