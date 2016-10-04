#pragma once

#include <QString>
#include <QList>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include "dependency.h"
#include "pipeline.h"

class ModManager;

class Modification
{
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

    QString getId()
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
    void addContent(const QString & id, Pipeline * p);
    Pipeline * getContent(const QString & id);

    QDir modBasePath();
    ModManager *getModManager() const;

    Pipeline * getPipeline(const QString & id);

    QStringList getPipelineIds();

    void enableDefaults();
    QString getAuthor() const;
    void setAuthor(const QString &Author);
    QString getUrl() const;
    void setUrl(const QString &Url);
    QString getLicense() const;
    void setLicense(const QString &License);
};
