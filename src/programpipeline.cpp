#include "programpipeline.h"
#include "modification.h"
#include "externalprogram.h"
#include "modmanager.h"
#include "profile.h"
#include "pipeline.h"
#include "platform.h"
#include "launcherexecutable.h"
#include "utils.h"

ProgramPipeline::ProgramPipeline(Modification *mod, const QString &id) : Pipeline(mod, id)
{

}

ProgramPipeline::~ProgramPipeline()
{

}

ProgramPipeline *ProgramPipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    ProgramPipeline * pip = new ProgramPipeline(mod, id);

    if(!loadGenericFromJson(json, pip))
    {
        delete pip;
        return nullptr;
    }

    pip->setDefault(false);

    QJsonObject executables_map = json["program"].toObject();

    for(QString platformid : executables_map.keys())
    {
        Platform::Type platform = Platform::getPlatformFromString(platformid);
        pip->setProgram(platform, LauncherExecutable::loadFromJson(executables_map[platformid].toObject()));
    }

    bool blocking = true;

    if(json.keys().contains("blocking"))
    {
        blocking = json["blocking"].toBool();
    }

    pip->setBlocking(blocking);

    return pip;
}

void ProgramPipeline::setProgram(Platform::Type platform, const LauncherExecutable &executable)
{
    m_programs[platform] = executable;
}

QString ProgramPipeline::pipelineType() const
{
    return "program";
}

int ProgramPipeline::runProgram()
{
    mod()->getModManager()->profile()->fixCrazyness();

    LauncherExecutable executable = m_programs[Platform::getCurrentPlatform()];

    if(executable.empty())
    {
        getLogger().log(Logger::Error, "pipeline-program", id(), "run", "Could not run! No executable for this platform!");

        return -1;
    }

    // Resolve the executable
    QString exe_path = executable.executable();
    QString workdir_path = executable.workdir();
    QStringList resolvedarguments = QStringList(executable.arguments());

    if(mod()->getModManager()->isValidModUrl(exe_path))
        exe_path = mod()->getModManager()->resolveModUrl(exe_path);
    else
        exe_path = pipelineBaseDir().absolutePath() + "/" + exe_path;

    if(mod()->getModManager()->isValidModUrl(workdir_path))
        workdir_path = mod()->getModManager()->resolveModUrl(workdir_path);
    else
        workdir_path = pipelineBaseDir().absolutePath() + "/" + workdir_path;

    for(int i = 0; i < resolvedarguments.size(); ++i)
    {
        resolvedarguments[i] = mod()->getModManager()->autoResolveModUrls(resolvedarguments[i]);
    }

    if(QFileInfo(exe_path).exists() && QFileInfo(exe_path).isFile())
    {
        QFile f(exe_path);
        f.setPermissions(f.permissions() | QFile::ExeUser);
    }

    // Infuse it into the process
    QProcess process;

    ExternalProgram::tryToInfuse(&process, exe_path, resolvedarguments);


    process.setWorkingDirectory(workdir_path);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setProcessEnvironment(utils::joinEnvironments(processEnvironment(), executable.environment()));

    getLogger().log(Logger::Info, "pipeline-program", id(), "run", "Running " + process.program() + " " + process.arguments().join(" ") + " in " + process.workingDirectory());

    if(m_blocking)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        process.start();
        process.waitForFinished(-1);

        QApplication::restoreOverrideCursor();

        QString output(process.readAllStandardOutput());
        getLogger().log(Logger::Info, "pipeline-program", id(), "run-output", output);


        return process.exitCode();
    }
    else
    {
        process.start();

        return 0;
    }
}

Pipeline::PipelineType ProgramPipeline::pipelineMainType() const
{
    return PipelineType::ProgramPipeline;
}

bool ProgramPipeline::blocking() const
{
    return m_blocking;
}

void ProgramPipeline::setBlocking(bool blocking)
{
    m_blocking = blocking;
}

void ProgramPipeline::install()
{

}

void ProgramPipeline::uninstall()
{

}

int ProgramPipeline::prime(bool is_forced)
{
    return 0;
}

bool ProgramPipeline::alreadyPrimed()
{
    return true;
}
