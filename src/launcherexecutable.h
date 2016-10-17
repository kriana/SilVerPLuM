#ifndef LAUNCHEREXECUTABLE_H
#define LAUNCHEREXECUTABLE_H

#include <QString>
#include <QStringList>

class LauncherExecutable
{
public:
    LauncherExecutable();

    LauncherExecutable(const QString & executable, const QStringList & arguments = QStringList(), const QString& workdir = "");

    /**
     * @brief Returns the executable in mod-url format
     * @return
     */
    QString executable() const;

    /**
     * @brief Sets the executable in mod-url format
     * @param executable
     */
    void setExecutable(const QString &executable);

    /**
     * @brief Returns the arguments. They support mod-url entries
     * @return
     */
    QStringList arguments() const;

    /**
     * @brief Sets the arguments. Supports mod-url
     * @param arguments
     */
    void setArguments(const QStringList &arguments);

    /**
     * @brief Returns true if no executable is set
     * @return
     */
    bool empty() const;

    /**
     * @brief Returns the workdir of this launcher in mod-url format
     * @return
     */
    QString workdir() const;

    /**
     * @brief Sets the workdir in mod-url format
     * @param workdir
     */
    void setWorkdir(const QString &workdir);

private:

    QString m_executable;

    QStringList m_arguments;

    QString m_workdir;
};

#endif // LAUNCHEREXECUTABLE_H
