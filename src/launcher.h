#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QString>
#include <QObject>
#include <QMap>
#include <QProcess>
#include <QJsonObject>
#include <QJsonArray>
#include "platform.h"
#include "launcherexecutable.h"

class Profile;
class Pipeline;

/**
 * @brief A launcher executes the game or other processes after all launch configurations were done
 */
class Launcher : public QObject
{
    Q_OBJECT

public:    

    Launcher(Profile * p, Pipeline * pip = nullptr);

    ~Launcher();

    virtual void start();

    virtual void stop();

    QString id() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    void setExecutable(Platform::Type platform, const LauncherExecutable & exe);

    LauncherExecutable getExecutable(Platform::Type platform);

    static Launcher * loadFromJson(Profile * p, Pipeline * pip, const QString & id, const QJsonObject & json);

    Pipeline *getPipeline() const;

    Profile *getProfile() const;

private:

    QString m_id;

    QString m_name;

    QString m_description;

    QMap<Platform::Type, LauncherExecutable> m_executable;

    Profile * m_profile;

    Pipeline * m_pipeline;

    QProcess * m_process = nullptr;

private slots:

    void processFinished(int retcode);

    void processError(QProcess::ProcessError error);

signals:

    void finished(int retcode);
};

#endif // LAUNCHER_H
