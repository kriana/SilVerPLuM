#pragma once

#include <QString>
#include <QList>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QObject>
#include <QSet>
#include <QProcessEnvironment>
#include "dependency.h"
#include "pipeline.h"
#include "logger.h"

class ModManager;

class Modification : public QObject
{
    Q_OBJECT

private:

    ModManager * m_modManager;
    QDir m_modBasePath;
    QString m_Id;
    QString m_Name;
    QString m_Author;
    QString m_Url;
    QString m_License;
    QVersionNumber m_Version;
    QString m_Description;
    QList<Dependency> m_Dependencies;
    QList<Pipeline*> m_Pipelines;
    QSet<QString> m_PipelineIds;
    //Logger m_logger;
    QStringList m_provides;
    QStringList m_categories;

public:
    Modification(ModManager * modmgr, const QString & id);

    ~Modification();

    QString id()
    {
        return m_Id;
    }

    static Modification *loadFromJson(ModManager *modmgr, const QDir &basepath, const QJsonObject & json);

    /**
     * @brief Gets the name of this modification
     * @return
     */
    QString name() const;

    /**
     * @brief Sets the name
     * @param Name
     */
    void setName(const QString &Name);

    /**
     * @brief Gets the version
     * @return
     */
    QVersionNumber version() const;

    /**
     * @brief Sets the version
     * @param Version
     */
    void setVersion(const QVersionNumber &Version);

    /**
     * @brief Gets the description in Markdown format
     * @return
     */
    QString description() const;

    /**
     * @brief Sets the description in Markdown format
     * @param Description
     */
    void setDescription(const QString &Description);

    /**
     * @brief Adds a dependency
     * @param dep
     */
    void addDependency(const Dependency &dep);

    /**
     * @brief Gets the list of depencencies
     * @return
     */
    QList<Dependency> dependencies();

    /**
     * @brief Adds a pipeline
     * @param id
     * @param p
     */
    void addPipeline(const QString & id, Pipeline * p);

    /**
     * @brief Return the mod manager of this mod
     * @return
     */
    ModManager *getModManager() const;

    /**
     * @brief Gets the list of all pipelines
     * @return
     */
    QList<Pipeline*> getPipelines();

    /**
     * @brief Gets the pipeline with the id
     * @param id
     * @return
     */
    Pipeline * getPipeline(const QString & id);

    /**
     * @brief Returns a list of all pipeline IDs
     * @return
     */
    QStringList getPipelineIds();

    /**
     * @brief Enable the default mods
     * @return exitcode
     */
    int enableDefaults();

    /**
     * @brief Returns count of supported default mods
     * @return
     */
    QList<Pipeline*> getSupportedDefaultPipelines();

    /**
     * @brief Disables this mod
     */
    void disableAll();

    /**
     * @brief Disables default pipelines
     */
    void disableDefaults();

    /**
     * @brief Returns the author
     * @return
     */
    QString author() const;

    /**
     * @brief Sets the author
     * @param Author
     */
    void setAuthor(const QString &Author);

    /**
     * @brief Returns the URL
     * @return
     */
    QString url() const;

    /**
     * @brief Sets the URL
     * @param Url
     */
    void setUrl(const QString &Url);

    /**
     * @brief Gets the license
     * @return
     */
    QString license() const;

    /**
     * @brief Sets the license
     * @param License
     */
    void setLicense(const QString &License);

    /**
     * @brief Returns true if a pipeline is activated
     * @return
     */
    bool isPartiallyEnabled();

    /**
     * @brief Returns list of activated pipelines
     * @return
     */
    QList<Pipeline*> getEnabledPipelines();

    /**
     * @brief Returns true if the searchstring applies to this mod
     * @param searchstring_
     * @return
     */
    bool search(const QString & searchstring_);

    /**
     * @brief Returns list of all installed files
     * @return
     */
    QStringList installedFiles();

    /**
     * @brief Installs this mod
     */
    void install();

    /**
     * @brief Uninstalls this mod
     */
    void uninstall();

    /**
     * @brief Primes all activated pipelines
     * @param force
     * @return
     */
    int prime(bool force);

    /**
     * @brief Returns the base path of this mod
     * @return
     */
    QDir modBasePath() const;


    /**
     * @brief Gets the mod's logger
     * @return
     */
    Logger & getLogger();

    /**
     * @brief Exports this mod as zip file
     * @param path
     * @return
     */
    bool exportToZip(const QString &path);

    /**
     * @brief Returns list of IDs this mod provides
     * @return
     */
    QStringList getProvides() const;

    /**
     * @brief Sets list of IDs this mod provides
     * @param provides
     */
    void setProvides(const QStringList &provides);

    /**
     * @brief Builds the environment for the executed tools
     * @return
     */
    QProcessEnvironment processEnvironment();

    QStringList getCategories() const;

    void setCategories(const QStringList &categories);

    bool isInCategory(QString querycategory);

protected:

    /**
     * @brief Sets the base path of this mod
     * @param modBasePath
     */
    void setModBasePath(const QDir &modBasePath);

private slots:

    void modEnabledDisabled(const QString & modid, const QString & contentid, bool enabled);

signals:

    void contentEnabledDisabled(const QString & content, bool enabled);
};
