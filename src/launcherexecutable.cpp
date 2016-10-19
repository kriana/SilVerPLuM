#include "launcherexecutable.h"
#include <stdexcept>
#include <QJsonArray>

LauncherExecutable::LauncherExecutable()
{

}

LauncherExecutable::LauncherExecutable(const QString &executable, const QStringList &arguments, const QString &workdir)
{
    setExecutable(executable);
    setArguments(arguments);
    setWorkdir(workdir);
}

QString LauncherExecutable::executable() const
{
    return m_executable;
}

void LauncherExecutable::setExecutable(const QString &executable)
{
    m_executable = executable.trimmed();
}

QStringList LauncherExecutable::arguments() const
{
    return m_arguments;
}

void LauncherExecutable::setArguments(const QStringList &arguments)
{
    m_arguments = arguments;
}

bool LauncherExecutable::empty() const
{
    return m_executable.isEmpty();
}

QString LauncherExecutable::workdir() const
{
    return m_workdir;
}

void LauncherExecutable::setWorkdir(const QString &workdir)
{
    m_workdir = workdir;
}

QProcessEnvironment LauncherExecutable::environment() const
{
    return m_environment;
}

void LauncherExecutable::setEnvironment(const QProcessEnvironment &environment)
{
    m_environment = environment;
}

LauncherExecutable LauncherExecutable::loadFromJson(const QJsonObject &definition)
{
    QString exe = definition["executable"].toString();
    QString wd = definition["workdir"].toString();
    QStringList args;
    QProcessEnvironment env;

    for(QJsonValue v : definition["arguments"].toArray())
    {
        args << v.toString();
    }

    QJsonObject env_map = definition["environment"].toObject();

    for(QString key : env_map.keys())
    {
        env.insert(key, env_map[key].toString());
    }

    LauncherExecutable le;
    le.setExecutable(exe);
    le.setWorkdir(wd);
    le.setArguments(args);
    le.setEnvironment(env);

    return le;
}
