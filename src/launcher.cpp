#include "launcher.h"
#include "profile.h"
#include "pipeline.h"
#include "game.h"
#include "utils.h"
#include "externalprogram.h"

Launcher::Launcher(Profile *p, Pipeline *pip) : m_profile(p), m_pipeline(pip)
{

}

Launcher::~Launcher()
{   
}

void Launcher::start()
{
    LauncherExecutable executable = getExecutable(Platform::getCurrentPlatform());

    if(executable.empty())
    {
        getProfile()->getLogger().log(Logger::Error, "launcher", id(), "start", "Could not run! No executable for this platform!");

        emit finished(-1);
        return;
    }

    // First fix crazyness
    m_profile->fixCrazyness();

    QString path = m_profile->getModManager()->resolveModUrl(executable.executable());
    QString workdir = m_profile->getModManager()->resolveModUrl(executable.workdir());


    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "start", "Executable url: " + executable.executable());
    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "start", "Absolute executable path: " + path);


    if(!QFileInfo(path).exists() || !QFileInfo(path).isFile())
    {
        getProfile()->getLogger().log(Logger::Error, "launcher", id(), "start", "Could not run! Executable does not exist!");

        emit finished(-1);
        return;
    }

    if(workdir.isEmpty())
    {
        getProfile()->getLogger().log(Logger::Warning, "launcher", id(), "start", "Workdir is empty. Set it to executable directory.");
        workdir = QFileInfo(path).absoluteDir().absolutePath();
    }

    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "start", "Absolute workdir path: " + workdir);

    if(workdir.isEmpty() || !QFileInfo(workdir).exists() || !QFileInfo(workdir).isDir())
    {
        getProfile()->getLogger().log(Logger::Error, "launcher", id(), "start", "Could not run! Workdir is no directory or doesn't exist!");

        emit finished(-1);
        return;
    }

    // Set permissions to executable
    QFile(path).setPermissions(QFile(path).permissions() | QFile::ExeUser);

    if(m_process != nullptr)
        m_process->deleteLater();

    m_process = new QProcess(this);

    /*QFile launcherfile(m_profile->StardewValleyDir().absoluteFilePath("SilVerPLuM.launcher.unix.sh"));
    if(launcherfile.exists())
        launcherfile.remove();*/

    QStringList resolvedarguments = QStringList(executable.arguments());

    for(int i = 0; i < resolvedarguments.size(); ++i)
    {
        resolvedarguments[i] = m_profile->getModManager()->autoResolveModUrls(resolvedarguments[i]);
    }

    ExternalProgram::tryToInfuse(m_process, path, resolvedarguments);

//    if(Platform::getCurrentPlatform() == Platform::Windows)
//    {
//        m_process->setProgram(path);
//        m_process->setArguments(resolvedarguments);
//    }
//    else
//    {
//        // OSX and Linux: Wrap around bash, so it will run everything
//        m_process->setProgram("/bin/bash");

//        /*
//         * Problem: If I close bash, the children will be still there
//         * Problem: I need to use bash, otherwise nothing will start
//         * Solution: Create a script that is placed somewhere that runs everything
//         */

//        // FUCK didn't work
//        /*if(launcherfile.open(QFile::WriteOnly))
//        {
//            QString template_script = utils::readAllTextFrom(":/resources/unix_launcher.sh");
//            QString command = (path + " " + executable.arguments().join(" ")).trimmed();
//            command = command.replace(" ", "\\ "); // Escape spaces
//            command = command.replace("\"", "\\\""); // Escape quotes

//            template_script = template_script.replace("{}", command);
//            QTextStream stream(&launcherfile);
//            stream << template_script;
//            launcherfile.close();

//            m_process->setArguments( QStringList() << launcherfile.fileName());
//        }
//        else*/
//        {
//            // Use old solution (which also doesn't work, but isn't as complex)
//            QString bash_argument = "";
//            bash_argument += (path + " " + resolvedarguments.join(" ")).trimmed();

//            bash_argument = bash_argument.replace("\"", "\\\""); // Escape quotes
//            bash_argument = "\"" + bash_argument + "\"";

//            m_process->setArguments( QStringList() << "-c" << bash_argument);
//        }
//    }

    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "start", "Running " + m_process->program() + " " + m_process->arguments().join(" "));

    m_process->setWorkingDirectory(m_profile->StardewValleyDir().absolutePath());
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    m_process->setProcessEnvironment(utils::joinEnvironments(m_profile->processEnvironment(), executable.environment()));

    connect(m_process, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
    connect(m_process, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    m_process->start();
}

void Launcher::stop()
{
    if(m_process != nullptr && m_process->isOpen())
    {
        switch(Platform::getCurrentPlatform())
        {
        case Platform::Windows:
            m_process->kill();
            break;
        case Platform::Linux:
            m_process->terminate();
            break;
        case Platform::Mac:
            m_process->terminate();
            break;
        }
    }
}

QString Launcher::id() const
{
    return m_id;
}

void Launcher::setId(const QString &id)
{
    m_id = id;
}

QString Launcher::name() const
{
    return m_name;
}

void Launcher::setName(const QString &name)
{
    m_name = name;
}

QString Launcher::description() const
{
    return m_description;
}

void Launcher::setDescription(const QString &description)
{
    m_description = description;
}

void Launcher::setExecutable(Platform::Type platform, const LauncherExecutable &exe)
{
    m_executable[platform] = exe;
}

LauncherExecutable Launcher::getExecutable(Platform::Type platform)
{
    return m_executable[platform];
}

Launcher *Launcher::loadFromJson(Profile * p, Pipeline *pip, const QString &id, const QJsonObject &json)
{
    qInfo() << "Loading launcher " << id << " in profile " << p->id();

    Launcher * launcher = new Launcher(p, pip);

    launcher->setId(id);
    launcher->setName(json["name"].toString());
    launcher->setDescription(json["description"].toString());

    QJsonObject executables_map = json["executables"].toObject();

    for(QString platformid : executables_map.keys())
    {
        Platform::Type platform = Platform::getPlatformFromString(platformid);
        launcher->setExecutable(platform, LauncherExecutable::loadFromJson(executables_map[platformid].toObject()));
    }

    return launcher;
}

Pipeline *Launcher::getPipeline() const
{
    return m_pipeline;
}

Profile *Launcher::getProfile() const
{
    return m_profile;
}

void Launcher::processFinished(int retcode)
{
    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "finished-output", QString(m_process->readAllStandardOutput()));
    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "finished", "Process finished with exit code " + QString::number(retcode));

    emit finished(retcode);
}

void Launcher::processError(QProcess::ProcessError error)
{
    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "finished-output", QString(m_process->readAllStandardOutput()));
    getProfile()->getLogger().log(Logger::Error, "launcher", id(), "finished", "Process finished with error QProcess::ProcessError::" + QString::number(error));

    emit finished(-1);
}

void Launcher::processReadyRead()
{
    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "process-output", QString(m_process->readAllStandardOutput()));
}
