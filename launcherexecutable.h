#ifndef LAUNCHEREXECUTABLE_H
#define LAUNCHEREXECUTABLE_H

#include <QString>
#include <QStringList>

class LauncherExecutable
{
public:
    LauncherExecutable();

    LauncherExecutable(const QString & executable, const QStringList & arguments = QStringList());

    QString executable() const;
    void setExecutable(const QString &executable);

    QStringList arguments() const;
    void setArguments(const QStringList &arguments);

    bool empty() const;

private:

    QString m_executable;

    QStringList m_arguments;
};

#endif // LAUNCHEREXECUTABLE_H
