#include "launcher.h"
#include "profile.h"
#include "game.h"

Launcher::Launcher(Profile *p) : m_profile(p)
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
        Game::instance()->log("Could not run! No executable for this platform!");
        emit finished(-1);
        return;
    }

    QString path = m_profile->StardewValleyDir().absoluteFilePath(executable.executable());

    Game::instance()->log("Running: " + path);

    if(!QFileInfo(path).exists())
    {
        Game::instance()->log("Could not run! Executable does not exist!");
        emit finished(-1);
        return;
    }

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

    Game::instance()->log(m_process->program() + " " + m_process->arguments().join(" "));

    m_process->setWorkingDirectory(m_profile->StardewValleyDir().absolutePath());

    connect(m_process, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
    m_process->start();
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

Profile *Launcher::profile() const
{
    return m_profile;
}

void Launcher::processFinished(int retcode)
{
    Game::instance()->log("Process finished with exit code " + QString::number(retcode));
    emit finished(retcode);
}

void Launcher::processError(QProcess::ProcessError error)
{
    Game::instance()->log("Process finished with error QProcess::ProcessError::" + QString::number(error));

    emit finished(-1);
}
