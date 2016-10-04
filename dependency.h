#pragma once
#include <QString>
#include <QVersionNumber>

class Dependency
{
public:

    enum Operation
    {
        EQUALS,
        LESS_THAN,
        MORE_THAN,
        EQUALS_OR_LESS_THAN,
        EQUALS_OR_MORE_THAN
    };

private:

    QString m_Id;
    Operation m_Operation;
    QVersionNumber m_Version;

public:

    Dependency(const QString &dependencystring);

    Dependency(const QString & id, Operation op, const QVersionNumber & version);

    QString getId();

    Operation getOperation();

    QVersionNumber getVersion();
};
