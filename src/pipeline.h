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

    struct EncryptionEntry
    {
        QString zipfile;
        QString password;
        QString destination;
        QStringList keep;
    };

    Pipeline(Modification * mod, const QString & id);

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

    virtual int primePipeline(bool force);

    bool isdefault() const;

    void setDefault(bool isdefault);

    QString id() const;

    bool isEnabled();

    int setEnabled(bool enabled);

    QDir pipelineBaseDir();

    bool unsupported() const;

    void setUnsupported(bool unsupported);

    virtual bool search(const QString & searchstring_);

    QList<Launcher *> launchers() const;

    virtual void install();

    virtual void uninstall();

    Logger & getLogger();

    QList<EncryptionEntry> getEncryptionEntries() const;

    void addEncryptionEntry(const EncryptionEntry & entry);

    static Pipeline * loadFromJson(Modification *mod, const QString &id, const QJsonObject &json);

protected:

    static bool loadGenericFromJson(const QJsonObject & json, Pipeline *pip);

    virtual QMap<QString, QString> resolveInstallables();

    virtual bool alreadyPrimed();

    virtual int prime();

private:

    Modification * m_mod;

    QString m_id;

    QString m_name;

    QString m_description;

    int m_priority;

    bool m_default;

    bool m_unsupported;

    QList<EncryptionEntry> m_encryptionEntries;

    QMap<QString, QString> m_installables;

    QMap<QString, Launcher *> m_launchers;

    Logger m_logger;

    QSet<QString> m_fgInstalledFiles;

private slots:

    void modEnabledDisabled(const QString & modid, const QString & contentid, bool enabled);

signals:

    void contentEnabledDisabled(bool enabled);
};
