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

    int prime(bool is_forced);

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

    /**
     * @brief Returns the relative path of source files
     * @return
     */
    QString sourceDirectory() const;

    void setSourceDirectory(const QString &sourceDirectory);

    /**
     * @brief Returns the directory containing the source files
     * @return
     */
    QDir pipelineSourceDir();

    /**
     * @brief The process environment that is applied to processes started from this pipeline
     * @return
     */
    QProcessEnvironment processEnvironment();

    /**
     * @brief The type of this pipeline
     * @return
     */
    QString pipelineType() const;


private:

    bool m_enableNugetRestore;

    QString m_sourceDirectory;

    QMap<QString, QString> m_referenceMap;

    QMap<QString, QStringList> m_buildArguments;

    DllPipeline(Modification * mod, const QString &id);

    bool alreadyPrimed();

    void writePrimeFile();

    int runNuget();

    int runMSBuild();

    void fixReferences(const QString &projectFile);       

    void addReferenceNode(QDomDocument &doc, QDomNode & parent, const QString & reference, const QString & hintpath, bool isprivate, bool specificversion);
};

#endif // DLLPIPELINE_H
