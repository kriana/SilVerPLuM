#ifndef MODMANAGER_H
#define MODMANAGER_H

#include <QDir>
#include <QString>
#include <QMap>
#include <QList>
#include <QSet>
#include <QSettings>
#include <QObject>
#include "modification.h"
#include "logger.h"

class Profile;

class ModManager : public QObject
{

    Q_OBJECT

public:

    static const QStringList FORBIDDEN_MOD_IDS;

    ModManager(Profile * profile);

    ~ModManager();

    /**
     * @brief Returns the profile of this mod manager
     * @return
     */
    Profile *profile() const;

    /**
     * @brief Initialized this mod manager
     */
    void initialize();

    /**
     * @brief Gets a list of all mods. Sorted by priority.
     * @return
     */
    QList<Modification*> getModifications();

    /**
     * @brief Gets the modification with id
     * @param id
     * @return
     */
    Modification * getModification(const QString & id);

    /**
     * @brief Gets a mod pipelines with id
     * @param mod
     * @param content
     * @return
     */
    Pipeline * getPipeline(const QString & mod, const QString & content);

    /**
     * @brief Enables/disables a pipeline
     * @param mod
     * @param content
     * @param enabled
     * @return exitcode
     */
    int setEnabled(const QString & mod, const QString & content, bool enabled);

    /**
     * @brief Returns true if the pipeline is enabled
     * @param mod
     * @param content
     * @return
     */
    bool isEnabled(const QString & mod, const QString & content);

    /**
     * @brief Moves a mod to a higher priority
     * @param mod
     * @return
     */
    bool priotizeUp(const QString & mod);

    /**
     * @brief Moves a mod to a lover priority
     * @param mod
     * @return
     */
    bool priotizeDown(const QString & mod);

    /**
     * @brief Returns true if the dependency satisfies one of the mod's dependencies
     * @param dep
     * @param requester
     * @param priorityaware
     * @return
     */
    bool dependencySatisfied(const Dependency & dep, Modification *requester, bool priorityaware);

    /**
     * @brief Returns a map of all unsatisfied dependencies based on mod id
     * @return
     */
    QMap<QString, QList<Dependency> > getUnsatisfiedDependencies() const;

    /**
     * @brief Installs all activated mods
     */
    void install();

    /**
     * @brief Uninstalls all activated mods
     */
    void uninstall();

    /**
     * @brief Resolves all valid mod URLs in content
     * @param content
     * @return
     */
    QString autoResolveModUrls(QString content);

    /**
     * @brief Resolves mod file paths like modid://file
     * @param url
     * @return
     */
    QString resolveModUrl(const QString & url, bool emptyoninvalid = true);

    /**
     * @brief Returns true if the parameter is a valid mod-url
     * @param url
     * @return
     */
    bool isValidModUrl(const QString & url);

    /**
     * @brief Returns the logger of this modmanager
     * @return
     */
    Logger & getLogger();

    /**
     * @brief Imports a mod from a directory
     * @param dir
     * @return
     */
    bool importModFromDirectory(const QDir & dir);

    /**
     * @brief Imports a mod from a *.zip file
     * @param filename
     * @return
     */
    bool importModFromZip(const QString & filename);

    /**
     * @brief Deletes a mod from ID
     * @param modid
     */
    void deleteMod(const QString & modid);

    /**
     * @brief Copies a mod to profile
     * @param modid
     * @param p
     */
    void copyModTo(const QString & modid, Profile * p);

public slots:

    /**
     * @brief Reloads all mods
     */
    void reloadMods();

    /**
     * @brief Issues a dependency check. It will signal when it's finished
     */
    void issueDependencyCheck();

private:

    QSettings * m_config;

    Profile * m_profile;

    QSet<QString> m_modId;

    QList<Modification*> m_mods;

    QMap<QString, QList<Dependency>> m_unsatisfiedDependencies;

    Logger m_logger;

    /**
     * @brief Priority used for sorting the mod list
     * @param mod
     * @return
     */
    int getSortPriority(const QString & mod);

    void writePriorities();

    bool loadMod(const QDir & directory);

    void sortMods();

signals:

    void updatedModList();

    void updatedModStatus(const QString & modid, const QString & contentid, bool enabled);

    void updatedDependencyCheck();

};

#endif // MODMANAGER_H
