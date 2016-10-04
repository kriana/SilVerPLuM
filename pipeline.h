#pragma once

#include <QString>
#include <QMap>

class Modification;

class Pipeline
{
public:

    virtual ~Pipeline();

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int priority() const;
    void setPriority(int priority);

    Modification *mod() const;

    void setInstallable(const QString & src, const QString & dst);

    /**
     * @brief This function is called to create missing files for installation
     */
    virtual void prime() = 0;

    bool isdefault() const;
    void setDefault(bool isdefault);

    QString id() const;

protected:

    Pipeline(Modification * mod, const QString & id);

private:

    Modification * m_mod;

    QString m_id;

    QString m_name;

    QString m_description;

    int m_priority;

    bool m_default;

    QMap<QString, QString> m_installables;
};
