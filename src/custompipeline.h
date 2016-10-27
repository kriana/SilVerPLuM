#ifndef CUSTOMPIPELINE_H
#define CUSTOMPIPELINE_H

#include "pipeline.h"
#include <QMap>
#include "launcherexecutable.h"
#include "platform.h"
#include <QProcessEnvironment>

/**
 * @brief The custom pipline will call a user-program or script
 */
class CustomPipeline : public Pipeline
{
public:
    ~CustomPipeline();

    static CustomPipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    bool prime(bool is_forced);

    void setScript(Platform::Type platform, const LauncherExecutable & executable);

    QProcessEnvironment processEnvironment(bool force);

    /**
     * @brief The type of this pipeline
     * @return
     */
    virtual QString pipelineType() const;

private:

    QMap<Platform::Type, LauncherExecutable> m_scripts;

    CustomPipeline(Modification * mod, const QString &id);

    bool alreadyPrimed();    
};

#endif // CUSTOMPIPELINE_H
