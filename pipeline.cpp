#include "pipeline.h"
#include "modification.h"
#include "modmanager.h"

Pipeline::Pipeline(Modification *mod, const QString &id) : m_mod(mod), m_id(id)
{
    connect(mod->getModManager(),
            SIGNAL(modEnabledDisabled(QString,QString,bool)),
            this,
            SLOT(modEnabledDisabled(QString,QString,bool)));
}

bool Pipeline::unsupported() const
{
    return m_unsupported;
}

void Pipeline::setUnsupported(bool unsupported)
{
    m_unsupported = unsupported;
}

bool Pipeline::search(const QString &searchstring_)
{
    QString searchstring = searchstring_.toLower();

    return name().toLower().contains(searchstring) ||
            description().toLower().contains(searchstring) ||
            id().toLower().contains(searchstring);
}

void Pipeline::modEnabledDisabled(const QString &modid, const QString &contentid, bool enabled)
{
    if(modid == m_mod->id() && contentid == m_id)
    {
        emit contentEnabledDisabled(enabled);
    }
}

QString Pipeline::id() const
{
    return m_id;
}

bool Pipeline::isEnabled()
{
    return m_mod->getModManager()->isEnabled(m_mod->id(), id());
}

void Pipeline::setEnabled(bool enabled)
{
    m_mod->getModManager()->setEnabled(m_mod->id(), id(), enabled);
}

QDir Pipeline::profileBaseDir()
{
    return m_mod->modBasePath().absoluteFilePath(id());
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
