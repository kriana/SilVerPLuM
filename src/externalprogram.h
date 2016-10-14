#pragma once

#include <QString>
#include <QStringList>
#include "launcherexecutable.h"
#include <QProcess>
#include <QMimeType>

class ExternalProgram
{
public:
    ExternalProgram();

    /**
     * @brief ExternalProgram
     * @param executables List of possible executables. Will automatically select the existing one
     * @param arguments
     * @param mimetypes
     */
    ExternalProgram(const QStringList & executables, const QStringList &arguments, const QStringList & mimetypes, bool runnable);

    /**
     * @brief Gets the path of the executable
     * @return
     */
    QString executablePath() const;

    /**
     * @brief Sets the path of the executable
     * @param executablePath
     */
    void setExecutablePath(const QString &executablePath);

    /**
     * @brief Gets the argument list
     * @return
     */
    QStringList arguments() const;

    /**
     * @brief Sets the arguments of this external Program
     * @param arguments
     */
    void setArguments(const QStringList &arguments);

    /**
     * @brief Sets ID of this external program
     * @param id
     */
    void setId(const QString &id);

    /**
     * @brief Returns true if this external program is not usable
     * @return
     */
    bool isEmpty() const;

    /**
     * @brief Returns the list of mimetypes this external program will run
     * @return
     */
    QStringList runtimeMimeTypes() const;

    /**
     * @brief Set the list of mimetypes this external program will run
     * @param runtimeMimeTypes
     */
    void setRuntimeMimeTypes(const QStringList &runtimeMimeTypes);

    /**
     * @brief Returns true if this program is runnable
     * @return
     */
    bool runnable() const;

    /**
     * @brief Sets/unsets if this program can run
     * @param runnable
     */
    void setRunnable(bool runnable);

    /**
     * @brief Returns if this program runs
     * @param type
     * @return
     */
    bool supportsMime(const QMimeType & type);

    /**
     * @brief Infuses this program's settings into a process
     * @param process
     */
    bool infuse(QProcess * process, const QString &file, const QStringList & args);

    /**
     * @brief Tries to figure out the correct runtime for the file and infuses it into the process
     * @param process
     * @param file
     * @param args
     * @return
     */
    static bool tryToInfuse(QProcess * process, const QString & file, const QStringList & args);

private:

    QString m_executablePath;
    QStringList m_arguments;
    QStringList m_runtimeMimeTypes;
    bool m_runnable;
};
