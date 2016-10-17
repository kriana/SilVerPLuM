#pragma once
#include <QString>
#include <QVersionNumber>

class Modification;

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

    /**
     * @brief Returns the mod-id of this dependency
     * @return
     */
    QString getId() const;

    /**
     * @brief Gets the operation of this dependency
     * @return
     */
    Operation getOperation() const;

    /**
     * @brief Gets the required version of this dependency
     * @return
     */
    QVersionNumber getVersion() const;

    /**
     * @brief Formats this dependency to a valid dependency string
     * @return
     */
    QString toString() const;

    /**
     * @brief Formats this dependency to a more readable string. Cannot be read into a dependency, again.
     * @return
     */
    QString toPrettyString() const;

    /**
     * @brief Determines if parameters satisfy this dependency
     * @param id
     * @param version
     * @return
     */
    bool satisfies(const QString & id, const QVersionNumber & version) const;

    /**
     * @brief Determines if a mod satisfies a dependency
     * @param mod
     * @return
     */
    bool satisfies(Modification * mod) const;
};
