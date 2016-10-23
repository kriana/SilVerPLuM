#include "dependencytree.h"
#include "modmanager.h"
#include "profile.h"
#include <QSet>
#include <QQueue>

DependencyTree::DependencyTree(ModManager *mgr) : m_modManager(mgr)
{

}

DependencyTree::~DependencyTree()
{

}

bool DependencyTree::resolveMetaDependency(const Dependency &dep)
{
    // Meta dependencies
    if(dep.getId() == "stardewvalley")
    {
        QVersionNumber sdvv = m_modManager->profile()->StardewValleyVersion();

        if(sdvv.majorVersion() == 0)
            return true;
        else
            return dep.satisfies("stardewvalley", sdvv);
    }

    return false;
}

Modification *DependencyTree::resolveDependency(const Dependency &dep)
{
    for(Modification * mod : m_modManager->getModifications())
    {
        if(dep.satisfies(mod))
            return mod;
    }

    return nullptr;
}

DependencyTree::DependencyCheckResult DependencyTree::dependenciesFulfilled(Modification *rootmod, bool priorityaware, bool complete)
{
    DependencyCheckResult result;

    TreeNode * root = m_modNodes[rootmod];
    int rootpriority = m_modManager->getModifications().indexOf(rootmod);
    QSet<TreeNode*> visited;
    QQueue<TreeNode*> stack;

    visited << root;
    result.unresolved << root->unresolved;

    for(Modification * dep : root->dependencies)
    {
        stack.enqueue(m_modNodes[dep]);
    }

    while(!stack.isEmpty())
    {
        TreeNode * nd  = stack.dequeue();
        visited << nd;

        result.unresolved << nd->unresolved;

        Modification * m = nd->modification;
        bool present = false;

        if(m->isPartiallyEnabled())
        {
            if(priorityaware)
            {
                present = m_modManager->getModifications().indexOf(m) < rootpriority;
            }
            else
            {
                present = true;
            }
        }

        if(!present)
            result.missing << m;

        // If not present or we want a complete report, put into stack
        if(!present || complete)
        {
            for(Modification * dep : m_modNodes[m]->dependencies)
            {
                stack.enqueue(m_modNodes[dep]);
            }
        }
    }

    return result;
}

void DependencyTree::rebuildTree()
{
    for(TreeNode * nd : m_nodes)
    {
        delete nd;
    }

    m_nodes.clear();
    m_modNodes.clear();

    for(Modification * mod : m_modManager->getModifications())
    {
        TreeNode * nd = new TreeNode();
        m_nodes << nd;
        m_modNodes[mod] = nd;

        nd->modification = mod;

        for(const Dependency & dep : mod->dependencies())
        {
            if(!resolveMetaDependency(dep))
            {
                Modification * resv = resolveDependency(dep);

                if(resv == nullptr)
                {
                    nd->unresolved << dep;
                }
                else
                {
                    nd->dependencies << resv;
                }
            }
        }
    }
}
