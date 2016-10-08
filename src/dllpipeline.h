#ifndef DLLPIPELINE_H
#define DLLPIPELINE_H

#include "pipeline.h"
#include <QtXml>


class DllPipeline : public Pipeline
{

public:

    ~DllPipeline();

    static DllPipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    int prime();

    bool enableNugetRestore() const;

    void setEnableNugetRestore(bool enableNugetRestore);

    QMap<QString, QString> referenceMap() const;

    /**
     * @brief setReferenceMapping
     * @param reference The reference name of the dependency. No version information etc.
     * @param locationurl Location of the reference as mod url.
     */
    void setReferenceMapping(const QString & reference, const QString & locationurl);

private:

    bool m_enableNugetRestore;

    QMap<QString, QString> m_referenceMap;

    DllPipeline(Modification * mod, const QString &id);

    bool alreadyPrimed();

    void writePrimeFile();

    int runNuget();

    int runMSBUILD();

    void fixReferences(const QString &projectFile);       

    void addReferenceNode(QDomDocument &doc, QDomNode & parent, const QString & reference, const QString & hintpath, bool isprivate, bool specificversion);
};

#endif // DLLPIPELINE_H
