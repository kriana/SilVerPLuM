#pragma once

#include <QString>
#include <QList>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QObject>
#include "dependency.h"
#include "pipeline.h"

class ModManager;

class Modification : public QObject
{
    Q_OBJECT

private:

    ModManager * m_modManager;
    QString m_Id;
    QString m_Name;
    QString m_Author;
    QString m_Url;
    QString m_License;
    QVersionNumber m_Version;
    QString m_Description;
    QList<Dependency*> m_Dependencies;
    QMap<QString, Pipeline*> m_Content;

public:
    Modification(ModManager * modmgr, const QString & id);

    ~Modification();

    QString id()
    {
        return m_Id;
    }

    static Modification *loadFromJson(ModManager *modmgr, const QJsonObject & json);

    QString name() const;
    void setName(const QString &Name);
    QVersionNumber version() const;
    void setVersion(const QVersionNumber &Version);
    QString description() const;
    void setDescription(const QString &Description);
    void addDependency(Dependency * dep);
    QList<Dependency *> dependencies();
    void addContent(const QString & id, Pipeline * p);
    Pipeline * getContent(const QString & id);

    QDir modBasePath();
    ModManager *getModManager() const;

    QList<Pipeline*> getPipelines();

    Pipeline * getPipeline(const QString & id);

    QStringList getPipelineIds();

    void enableDefaults();

    void disableAll();

    QString author() const;
    void setAuthor(const QString &Author);
    QString url() const;
    void setUrl(const QString &Url);
    QString license() const;
    void setLicense(const QString &License);

    bool isPartiallyEnabled();

    QList<Pipeline*> getEnabledPipelines();

    bool search(const QString & searchstring_);

private slots:

    void modEnabledDisabled(const QString & modid, const QString & contentid, bool enabled);

signals:

    void contentEnabledDisabled(const QString & content, bool enabled);
};
