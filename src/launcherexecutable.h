#ifndef LAUNCHEREXECUTABLE_H
#define LAUNCHEREXECUTABLE_H

#include <QString>
#include <QStringList>

class LauncherExecutable
{
public:
    LauncherExecutable();

    LauncherExecutable(const QString & executable, const QStringList & arguments = QStringList(), const QString& workdir = "");

    QString executable() const;
    void setExecutable(const QString &executable);

    QStringList arguments() const;
    void setArguments(const QStringList &arguments);

    bool empty() const;

    QString workdir() const;

    void setWorkdir(const QString &workdir);

private:

    QString m_executable;

    QStringList m_arguments;

    QString m_workdir;
};

#endif // LAUNCHEREXECUTABLE_H
