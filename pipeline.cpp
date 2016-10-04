#include "pipeline.h"

Pipeline::Pipeline(Modification *mod, const QString &id) : m_mod(mod), m_id(id)
{

}

QString Pipeline::id() const
{
    return m_id;
}

Pipeline::~Pipeline()
{

}

QString Pipeline::name() const
{
    return m_name;
}

void Pipeline::setName(const QString &name)
{
    m_name = name;
}

QString Pipeline::description() const
{
    return m_description;
}

void Pipeline::setDescription(const QString &description)
{
    m_description = description;
}

int Pipeline::priority() const
{
    return m_priority;
}

void Pipeline::setPriority(int priority)
{
    m_priority = priority;
}

Modification *Pipeline::mod() const
{
    return m_mod;
}

void Pipeline::setInstallable(const QString &src, const QString &dst)
{
    m_installables[src] = dst;
}

bool Pipeline::isdefault() const
{
    return m_default;
}

void Pipeline::setDefault(bool isdefault)
{
    m_default = isdefault;
}
