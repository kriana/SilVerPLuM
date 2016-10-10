#ifndef DLLPIPELINE_H
#define DLLPIPELINE_H

#include "pipeline.h"
#include <QtXml>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class DllPipeline : public Pipeline
{

public:

    ~DllPipeline();

    static DllPipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    int prime(bool force);

    bool enableNugetRestore() const;

    void setEnableNugetRestore(bool enableNugetRestore);

    QMap<QString, QString> referenceMap() const;

    /**
     * @brief setReferenceMapping
     * @param reference The reference name of the dependency. No version information etc.
     * @param locationurl Location of the reference as mod url.
     */
    void setReferenceMapping(const QString & reference, const QString & locationurl);

    /**
     * @brief Sets parameters for msbuild/xbuild
     * @param platform
     * @param args
     */
    void setBuildParameters(const QString & platform, const QStringList & args);

    void downloadNugetIfNotExisting();

private:

    bool m_enableNugetRestore;

    QMap<QString, QString> m_referenceMap;

    QMap<QString, QStringList> m_buildArguments;

    DllPipeline(Modification * mod, const QString &id);

    bool alreadyPrimed();

    void writePrimeFile();

    int runNuget();

    int runMSBUILD();

    void fixReferences(const QString &projectFile);       

    void addReferenceNode(QDomDocument &doc, QDomNode & parent, const QString & reference, const QString & hintpath, bool isprivate, bool specificversion);
};

#endif // DLLPIPELINE_H
