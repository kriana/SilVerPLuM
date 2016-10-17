#include "dependency.h"
#include <QRegExp>
#include <stdexcept>
#include "modification.h"

Dependency::Dependency(const QString & dependencystring)
{
    QStringList cell = dependencystring.split(QRegExp("(<|>|=)"), QString::SkipEmptyParts);

    if(cell.size() != 2)
    {
        throw std::invalid_argument("Cannot decode dependency string! Cannot separate it!");
    }

    m_Id = cell[0];
    m_Version = QVersionNumber::fromString(cell[1]);

    if(dependencystring.contains("<="))
    {
        m_Operation = EQUALS_OR_LESS_THAN;
    }
    else if(dependencystring.contains(">="))
    {
        m_Operation = EQUALS_OR_MORE_THAN;
    }
    else if(dependencystring.contains("="))
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

QString Dependency::getId() const
{
    return m_Id;
}

Dependency::Operation Dependency::getOperation() const
{
    return m_Operation;
}

QVersionNumber Dependency::getVersion() const
{
    return m_Version;
}

QString Dependency::toString() const
{
    QString op;

    switch(getOperation())
    {
    case EQUALS:
        op = "=";
        break;
    case LESS_THAN:
        op = "<";
        break;
    case MORE_THAN:
        op = ">";
        break;
    case EQUALS_OR_LESS_THAN:
        op = "<=";
        break;
    case EQUALS_OR_MORE_THAN:
        op = ">=";
        break;
    default:
        op = "??";
        break;
    }

    return getId() + op + getVersion().toString();
}

QString Dependency::toPrettyString() const
{
    QString op;

    switch(getOperation())
    {
    case EQUALS:
        op = "=";
        break;
    case LESS_THAN:
        op = "<";
        break;
    case MORE_THAN:
        op = ">";
        break;
    case EQUALS_OR_LESS_THAN:
        op = "≤";
        break;
    case EQUALS_OR_MORE_THAN:
        op = "≥";
        break;
    default:
        op = "?";
        break;
    }

    return getId() + " " + op + " " + getVersion().toString();
}

bool Dependency::satisfies(const QString &id, const QVersionNumber &version) const
{
    if(id == getId())
    {
        switch(getOperation())
        {
        case EQUALS:
            return version == getVersion();
        case LESS_THAN:
            return version < getVersion();
        case MORE_THAN:
            return version > getVersion();
        case EQUALS_OR_LESS_THAN:
            return version <= getVersion();
        case EQUALS_OR_MORE_THAN:
            return version >= getVersion();
        default:
            return false;
        }
    }

    return false;
}

bool Dependency::satisfies(Modification *mod) const
{
    return satisfies(mod->id(), mod->version());
}
