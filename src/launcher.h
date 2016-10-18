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

    /**
     * @brief Starts this launcher
     */
    virtual void start();

    /**
     * @brief Tries to stop this launcher
     */
    virtual void stop();

    /**
     * @brief Get this launcher's ID
     * @return
     */
    QString id() const;

    /**
     * @brief Set this launcher's ID
     * @param id
     */
    void setId(const QString &id);

    /**
     * @brief Get this launcher's name
     * @return
     */
    QString name() const;

    /**
     * @brief Set this launcher's name
     * @param name
     */
    void setName(const QString &name);

    /**
     * @brief Get this launcher's description
     * @return
     */
    QString description() const;

    /**
     * @brief Sets this launcher's description
     * @param description
     */
    void setDescription(const QString &description);

    /**
     * @brief Sets this launcher's executable
     * @param platform
     * @param exe
     */
    void setExecutable(Platform::Type platform, const LauncherExecutable & exe);

    /**
     * @brief Get this launcher's executable
     * @param platform
     * @return
     */
    LauncherExecutable getExecutable(Platform::Type platform);

    /**
     * @brief Load this launcher from a configuration entry
     * @param p
     * @param pip
     * @param id
     * @param json
     * @return
     */
    static Launcher * loadFromJson(Profile * p, Pipeline * pip, const QString & id, const QJsonObject & json);

    /**
     * @brief Gets the pipline this launcher belongs to
     * @return
     */
    Pipeline *getPipeline() const;

    /**
     * @brief Gets the profile this launcher belongs to
     * @return
     */
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

    void processReadyRead();

signals:

    void finished(int retcode);
};

#endif // LAUNCHER_H
