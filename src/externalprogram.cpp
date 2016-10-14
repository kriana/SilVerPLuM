#include "externalprogram.h"
#include <QFile>
#include <QMimeDatabase>
#include "globalsettings.h"

ExternalProgram::ExternalProgram()
{

}

ExternalProgram::ExternalProgram(const QStringList &executables, const QStringList &arguments, const QStringList &mimetypes, bool runnable)
{
    for(QString exe : executables)
    {
        if(QFile(exe).exists(exe))
        {
            setExecutablePath(exe);
            break;
        }
    }

    if(isEmpty())
    {
        setExecutablePath(executables.first());
    }

    setArguments(arguments);
    setRuntimeMimeTypes(mimetypes);
    setRunnable(runnable);
}

QString ExternalProgram::executablePath() const
{
    return m_executablePath;
}

void ExternalProgram::setExecutablePath(const QString &executablePath)
{
    m_executablePath = executablePath;
}

QStringList ExternalProgram::arguments() const
{
    return m_arguments;
}

void ExternalProgram::setArguments(const QStringList &arguments)
{
    m_arguments = arguments;
}

QString ExternalProgram::id() const
{
    return m_id;
}

void ExternalProgram::setId(const QString &id)
{
    m_id = id;
}

bool ExternalProgram::isEmpty() const
{
    return m_executablePath.isEmpty();
}

QStringList ExternalProgram::runtimeMimeTypes() const
{
    return m_runtimeMimeTypes;
}

void ExternalProgram::setRuntimeMimeTypes(const QStringList &runtimeMimeTypes)
{
    m_runtimeMimeTypes = runtimeMimeTypes;
}

bool ExternalProgram::runnable() const
{
    return m_runnable;
}

void ExternalProgram::setRunnable(bool runnable)
{
    m_runnable = runnable;
}

bool ExternalProgram::infuse(QProcess *process, const QStringList &args)
{

}

bool ExternalProgram::tryToInfuse(QProcess *process, const QString &file, const QStringList &args)
{
    QMimeType mime = QMimeDatabase::mimeTypeForFile(file);

}
