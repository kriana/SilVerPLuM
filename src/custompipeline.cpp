#include "custompipeline.h"
#include "platform.h"
#include "utils.h"
#include "modification.h"
#include "modmanager.h"
#include "profile.h"
#include "externalprogram.h"

CustomPipeline::CustomPipeline(Modification *mod, const QString &id) : Pipeline(mod, id)
{

}

CustomPipeline::~CustomPipeline()
{

}

CustomPipeline *CustomPipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    CustomPipeline * pip = new CustomPipeline(mod, id);

    if(!loadGenericFromJson(json, pip))
    {
        delete pip;
        return nullptr;
    }

    QJsonObject executables_map = json["script"].toObject();

    for(QString platformid : executables_map.keys())
    {
        Platform::Type platform = Platform::getPlatformFromString(platformid);
        pip->setScript(platform, LauncherExecutable::loadFromJson(executables_map[platformid].toObject()));
    }

    return pip;
}

int CustomPipeline::prime(bool is_forced)
{
    mod()->getModManager()->profile()->fixCrazyness();

    LauncherExecutable executable = m_scripts[Platform::getCurrentPlatform()];

    if(executable.empty())
    {
        getLogger().log(Logger::Error, "pipeline-custom", id(), "prime", "Could not run! No executable for this platform!");

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
    process.setProcessEnvironment(utils::joinEnvironments(processEnvironment(is_forced), executable.environment()));

    getLogger().log(Logger::Info, "pipeline-custom", id(), "prime", "Running " + process.program() + " " + process.arguments().join(" ") + " in " + process.workingDirectory());

    process.start();
    process.waitForStarted(-1);
    if(process.state() != QProcess::Running)
    {
        getLogger().log(Logger::Error, "pipeline-custom", id(), "prime", "Failed to start process!");
        return -1;
    }
    process.waitForFinished(-1);

    QString output(process.readAllStandardOutput());
    getLogger().log(Logger::Info, "pipeline-custom", id(), "prime-output", output);


    return process.exitCode();
}

void CustomPipeline::setScript(Platform::Type platform, const LauncherExecutable &executable)
{
    m_scripts[platform] = executable;
}

QProcessEnvironment CustomPipeline::processEnvironment(bool force)
{
    QProcessEnvironment env = Pipeline::processEnvironment();

    env.insert("SILVERPLUM_FORCE_PRIME", force ? "1" : "0");
    env.insert("MOD_BUILDER", "Silverplum");

    return env;
}

QString CustomPipeline::pipelineType() const
{
    return "custom";
}

bool CustomPipeline::alreadyPrimed()
{
    return false; // The script is always called
}
