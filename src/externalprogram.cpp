#include "externalprogram.h"
#include <QFile>
#include <QMimeDatabase>
#include "globalsettings.h"
#include "utils.h"

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

bool ExternalProgram::supportsMime(QMimeDatabase & db, const QString filename)
{
    for(QString mime : m_runtimeMimeTypes)
    {
        QString extension;

        if(mime.contains("&"))
        {
            extension = mime.split("&").last();
            mime = mime.split("&").first();
        }

        if(!extension.isEmpty())
        {
            if(!filename.endsWith(extension))
                continue;
        }

        QMimeType type = db.mimeTypeForFile(filename);

        if(type.inherits(mime))
        {
            return true;
        }
    }

    return false;
}

bool ExternalProgram::infuse(QProcess *process, const QString & file, const QStringList &args)
{
    QStringList procargs = QStringList(m_arguments);
    QString joinedargs = utils::ArgumentListToString(args);
    QString joinedfileargs = utils::ArgumentListToString(QStringList() << file << args);

    // Resolve just replaced values
    for(int i = 0; i < procargs.size(); ++i)
    {
        procargs[i] = procargs[i].replace("{file}", file)
                .replace("{joinedargs}", joinedargs)
                .replace("{joinedfileargs}", joinedfileargs);
    }

    // Apply insert
    while(procargs.contains("{insertargs}"))
    {
        int index = procargs.indexOf("{insertargs}");

        for(int i = args.length() - 1; i >= 0; --i)
        {
            procargs.insert(index, args[i]);
        }

        index = procargs.indexOf("{insertargs}");
        procargs.removeAt(index);
    }

    process->setProgram(executablePath());
    process->setArguments(procargs);
    process->setProcessEnvironment(m_environment);

    return true;
}

bool ExternalProgram::tryToInfuse(QProcess *process, const QString &file, const QStringList &args)
{
    QMimeDatabase mimedb;

    QList<ExternalProgram> programs = GlobalSettings::instance()->getExternalPrograms();

    for(ExternalProgram program : programs)
    {
        if(program.runnable() && program.supportsMime(mimedb, file))
        {
            if(program.infuse(process, file, args))
            {
                return true;
            }
        }
    }

    // Infuse it as the file being the executable
    process->setProgram(file);
    process->setArguments(args);

    return false;
}

QProcessEnvironment ExternalProgram::environment() const
{
    return m_environment;
}

void ExternalProgram::setEnvironment(const QProcessEnvironment &environment)
{
    m_environment = environment;
}

void ExternalProgram::setEnvironmentVariable(const QString &var, const QString &value)
{
    m_environment.insert(var, value);
}
