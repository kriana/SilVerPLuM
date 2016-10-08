#include "launcherexecutable.h"
#include <stdexcept>

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
