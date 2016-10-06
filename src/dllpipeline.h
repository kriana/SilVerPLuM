#ifndef DLLPIPELINE_H
#define DLLPIPELINE_H

#include "pipeline.h"


class DllPipeline : public Pipeline
{

public:

    ~DllPipeline();

    static DllPipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    void prime();

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

    void runNuget();

    void fixReferences(const QString &projectFile);
};

#endif // DLLPIPELINE_H
