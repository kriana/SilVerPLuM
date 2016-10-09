#include "launcher.h"
#include "profile.h"
#include "pipeline.h"
#include "game.h"

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
        delete m_process;

    m_process = new QProcess(this);

    if(Platform::getCurrentPlatform() == Platform::Windows)
    {
        m_process->setProgram(executable.executable());
        m_process->setArguments(executable.arguments());
    }
    else
    {
        // OSX and Linux: Wrap around bash, so it will run everything
        m_process->setProgram("/bin/bash");
        QString bash_argument = (path + " " + executable.arguments().join(" ")).trimmed();

        // Fix the formatting for bash
        bash_argument = bash_argument.replace(" ", "\\ ");

        m_process->setArguments( QStringList() << "-c" << bash_argument);
    }

    getProfile()->getLogger().log(Logger::Info, "launcher", id(), "start", "Running " + m_process->program() + " " + m_process->arguments().join(" "));

    m_process->setWorkingDirectory(m_profile->StardewValleyDir().absolutePath());
    m_process->setProcessChannelMode(QProcess::MergedChannels);

    connect(m_process, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
    m_process->start();
}

void Launcher::stop()
{
    if(m_process != nullptr && m_process->isOpen())
    {
        m_process->kill();
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
        QString exe = executables_map[platformid].toObject()["executable"].toString();
        QString wd = executables_map[platformid].toObject()["workdir"].toString();
        QStringList args;

        for(QJsonValue v : executables_map[platformid].toObject()["arguments"].toArray())
        {
            args << v.toString();
        }

        launcher->setExecutable(platform, LauncherExecutable(exe, args, wd));
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
