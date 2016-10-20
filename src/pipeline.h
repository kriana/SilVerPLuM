#pragma once

#include <QString>
#include <QMap>
#include <QObject>
#include <QDir>
#include "logger.h"
#include <QProcessEnvironment>

class Modification;
class Launcher;

class Pipeline : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief A pipeline can be from different types. Content provides mod content. Program lets the user run a script, program, etc. Repository pipelines contain information about mod repositories
     */
    enum PipelineType
    {
        ContentPipeline,
        ProgramPipeline,
        RepositoryPipeline
    };

    /**
     * @brief Contains information about encrypted content
     */
    struct EncryptionEntry
    {
        QString zipfile;
        QString password;
        QString destination;
        QStringList keep;
    };

    Pipeline(Modification * mod, const QString & id);

    virtual ~Pipeline();

    /**
     * @brief The name of this pipeline
     * @return
     */
    QString name() const;

    /**
     * @brief Sets the name of this pipeline
     * @param name
     */
    void setName(const QString &name);

    /**
     * @brief Description of this pipeline in Markdown format
     * @return
     */
    QString description() const;

    /**
     * @brief Sets the description of this pipeline in Markdown format
     * @param description
     */
    void setDescription(const QString &description);

    /**
     * @brief Gets the priority of this pipeline
     * @return
     */
    int priority() const;

    /**
     * @brief Sets the priority of this pipeline
     * @param priority
     */
    void setPriority(int priority);

    /**
     * @brief Gets the mod this pipeline belongs to
     * @return
     */
    Modification *mod() const;

    /**
     * @brief Sets a file src installed to dst
     * @param src
     * @param dst
     */
    void setInstallable(const QString & src, const QString & dst);

    /**
     * @brief Inserts a launcher
     * @param id
     * @param launcher
     */
    void setLauncher(const QString & id, Launcher * launcher);

    /**
     * @brief Primes the pipeline. Will do preparation work such as building extracting encrypted content etc.
     * @param force
     * @return
     */
    virtual int primePipeline(bool force);

    /**
     * @brief Returns true if this pipeline is supposed to be installed by default
     * @return
     */
    bool isdefault() const;

    /**
     * @brief Set/Unset this pipeline to be installed by default
     * @param isdefault
     */
    void setDefault(bool isdefault);

    /**
     * @brief Gets the ID of this pipeline
     * @return
     */
    QString id() const;

    /**
     * @brief The type of this pipeline
     * @return
     */
    virtual QString pipelineType() const;

    /**
     * @brief Returns true if this pipeline was enabled
     * @return
     */
    bool isEnabled();

    /**
     * @brief Enables/disables this pipeline
     * @param enabled
     * @return exitcode
     */
    int setEnabled(bool enabled);

    /**
     * @brief Returns the directory of this pipeline
     * @return
     */
    QDir pipelineBaseDir();

    /**
     * @brief Returns true if this pipeline is not supported by this platform
     * @return
     */
    bool unsupported() const;

    /**
     * @brief Sets/unsets if this pipeline is not supported by this platform
     * @param unsupported
     */
    void setUnsupported(bool unsupported);

    /**
     * @brief Returns true if the searchsting applies to this pipeline
     * @param searchstring_
     * @return
     */
    virtual bool search(const QString & searchstring_);

    /**
     * @brief Returns the list of launchers
     * @return
     */
    QList<Launcher *> launchers() const;

    /**
     * @brief Installs this pipeline
     */
    virtual void install();

    /**
     * @brief Uninstalls this pipeline
     */
    virtual void uninstall();

    /**
     * @brief Gets the logger of this pipeline
     * @return
     */
    Logger & getLogger();

    /**
     * @brief Returns the list of encrypted content entries
     * @return
     */
    QList<EncryptionEntry> getEncryptionEntries() const;

    /**
     * @brief Adds an encrypted content entry
     * @param entry
     */
    void addEncryptionEntry(const EncryptionEntry & entry);

    /**
     * @brief Loads this pipeline from configuration
     * @param mod
     * @param id
     * @param json
     * @return
     */
    static Pipeline * loadFromJson(Modification *mod, const QString &id, const QJsonObject &json);

    /**
     * @brief List of pipeline-ids this pipeline can provide
     * @return
     */
    QStringList getProvides() const;

    /**
     * @brief Sets pipeline-ids that this pipeline can provide
     * @param provides
     */
    void setProvides(const QStringList &provides);

    /**
     * @brief Builds the environment for the executed tools
     * @return
     */
    virtual QProcessEnvironment processEnvironment();

    /**
     * @brief Runs the program associated to this pipeline. Used for ProgramPipeline.
     * @return
     */
    virtual int runProgram();

    /**
     * @brief Returns the repositories associated to this pipeline. Used by RepositoryPipeline.
     * @return
     */
    virtual QStringList repositories();

    /**
     * @brief The type of this pipeline
     * @return
     */
    virtual PipelineType pipelineMainType() const;

protected:

    static bool loadGenericFromJson(const QJsonObject & json, Pipeline *pip);

    virtual QMap<QString, QString> resolveInstallables();

    virtual bool alreadyPrimed();

    virtual int prime(bool is_forced);

private:

    Modification * m_mod;

    QString m_id;

    QString m_name;

    QString m_description;

    int m_priority;

    bool m_default;

    bool m_unsupported;

    QList<EncryptionEntry> m_encryptionEntries;

    QMap<QString, QString> m_installables;

    QMap<QString, Launcher *> m_launchers;

    Logger m_logger;

    QSet<QString> m_fgInstalledFiles;

    QStringList m_provides;

private slots:

    void modEnabledDisabled(const QString & modid, const QString & contentid, bool enabled);

signals:

    void contentEnabledDisabled(bool enabled);
};
