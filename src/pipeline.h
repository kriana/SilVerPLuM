#pragma once

#include <QString>
#include <QMap>
#include <QObject>
#include <QDir>
#include "logger.h"

class Modification;
class Launcher;

class Pipeline : public QObject
{
    Q_OBJECT

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

    void setLauncher(const QString & id, Launcher * launcher);

    /**
     * @brief This function is called to create missing files for installation
     */
    virtual int prime() = 0;

    bool isdefault() const;
    void setDefault(bool isdefault);

    QString id() const;

    bool isEnabled();

    void setEnabled(bool enabled);

    QDir pipelineBaseDir();

    bool unsupported() const;

    void setUnsupported(bool unsupported);

    virtual bool search(const QString & searchstring_);

    QList<Launcher *> launchers() const;

    virtual void install();

    Logger & getLogger();

protected:

    Pipeline(Modification * mod, const QString & id);

    static void loadGenericFromJson(const QJsonObject & json, Pipeline *pip);

    virtual QMap<QString, QString> resolveInstallables();

private:

    Modification * m_mod;

    QString m_id;

    QString m_name;

    QString m_description;

    int m_priority;

    bool m_default;

    bool m_unsupported;

    QMap<QString, QString> m_installables;

    QMap<QString, Launcher *> m_launchers;

    Logger m_logger;

private slots:

    void modEnabledDisabled(const QString & modid, const QString & contentid, bool enabled);

signals:

    void contentEnabledDisabled(bool enabled);
};
