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
        QString exe = executables_map[platformid].toObject()["executable"].toString();
        QString wd = executables_map[platformid].toObject()["workdir"].toString();
        QStringList args;

        for(QJsonValue v : executables_map[platformid].toObject()["arguments"].toArray())
        {
            args << v.toString();
        }

        pip->setScript(platform, LauncherExecutable(exe, args, wd));
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
    process.setProcessEnvironment(buildEnvironment(is_forced));

    getLogger().log(Logger::Info, "pipeline-custom", id(), "prime", "Running " + process.program() + " " + process.arguments().join(" ") + " in " + process.workingDirectory());

    process.start();
    process.waitForFinished(-1);

    QString output(process.readAllStandardOutput());
    getLogger().log(Logger::Info, "pipeline-custom", id(), "prime-output", output);


    return process.exitCode();
}

void CustomPipeline::setScript(Platform::Type platform, const LauncherExecutable &executable)
{
    m_scripts[platform] = executable;
}

bool CustomPipeline::alreadyPrimed()
{
    return false; // The script is always called
}

QProcessEnvironment CustomPipeline::buildEnvironment(bool force)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    env.insert("STARDEWVALLEY_DIR", mod()->getModManager()->profile()->StardewValleyDir().absolutePath());
    env.insert("STARDEWVALLEY_SAVEGAME_DIR", mod()->getModManager()->profile()->StardewValleySavegameDir().absolutePath());
    env.insert("STARDEWVALLEY_USERDATA_DIR", mod()->getModManager()->profile()->StardewValleyUserDataDir().absolutePath());
    env.insert("STARDEWVALLEY_PLATFORM", Platform::getPlatformString());
    env.insert("STARDEWVALLEY_TECHNOLOGY", mod()->getModManager()->profile()->StardewValleyTechnologyString());

    for(Modification * m : mod()->getModManager()->getModifications())
    {
        env.insert("SILVERPLUM_MOD_" + m->id().toUpper() + "_DIR", m->modBasePath().absolutePath());
    }

    env.insert("SILVERPLUM_FORCE_PRIME", force ? "true" : "false");

    return env;
}

