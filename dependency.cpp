#include "dependency.h"
#include <QRegExp>
#include <stdexcept>

Dependency::Dependency(const QString & dependencystring)
{
    QStringList cell = dependencystring.split(QRegExp("(<|>|=)"), QString::SkipEmptyParts);

    if(cell.size() != 2)
    {
        throw std::invalid_argument("Cannot decode dependency string! Cannot separate it!");
    }

    m_Id = cell[0];
    m_Version = QVersionNumber::fromString(cell[1]);

    if(dependencystring.contains("=="))
    {
        m_Operation = EQUALS;
    }
    else if(dependencystring.contains("<"))
    {
        m_Operation = LESS_THAN;
    }
    else if(dependencystring.contains(">"))
    {
        m_Operation = MORE_THAN;
    }
    else if(dependencystring.contains("<="))
    {
        m_Operation = EQUALS_OR_LESS_THAN;
    }
    else if(dependencystring.contains(">="))
    {
        m_Operation = EQUALS_OR_MORE_THAN;
    }
    else
    {
        throw std::invalid_argument("Cannot decode dependency string! No known operator!");
    }
}

Dependency::Dependency(const QString &id, Dependency::Operation op, const QVersionNumber &version) :
    m_Id(id),
    m_Operation(op),
    m_Version(version)
{

}

QString Dependency::getId()
{
    return m_Id;
}

Dependency::Operation Dependency::getOperation()
{
    return m_Operation;
}

QVersionNumber Dependency::getVersion()
{
    return m_Version;
}
