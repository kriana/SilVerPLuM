#ifndef PROGRAMPIPELINE_H
#define PROGRAMPIPELINE_H

#include "modification.h"
#include "launcherexecutable.h"
#include "platform.h"
#include <QProcessEnvironment>
#include "pipeline.h"

class ProgramPipeline : public Pipeline
{
public:
    ~ProgramPipeline();

    static ProgramPipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    void setProgram(Platform::Type platform, const LauncherExecutable & executable);

    /**
     * @brief The type of this pipeline
     * @return
     */
    virtual QString pipelineType() const;

    int runProgram();

    PipelineType pipelineMainType() const;

    /**
     * @brief Returns true if this program blocks SilVerPLuM
     * @return
     */
    bool blocking() const;

    void setBlocking(bool blocking);

    void install();

    void uninstall();

protected:

    int prime(bool is_forced);

    bool alreadyPrimed();

private:

    QMap<Platform::Type, LauncherExecutable> m_programs;

    bool m_blocking;

    ProgramPipeline(Modification * mod, const QString &id);


};

#endif // PROGRAMPIPELINE_H
