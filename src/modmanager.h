#ifndef MODMANAGER_H
#define MODMANAGER_H

#include <QDir>
#include <QString>
#include <QMap>
#include <QList>
#include <QSet>
#include <QSettings>
#include <QObject>
#include <QProcessEnvironment>
#include "modification.h"
#include "logger.h"
#include "modrepository.h"
#include "dependencytree.h"

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
     * @brief Gets list of all partially active mods. Sorted by priority.
     * @return
     */
    QList<Modification*> getPartiallyActiveMods();

    /**
     * @brief Orders the list of mods according to their priority
     * @param unordered
     * @return
     */
    QList<Modification*> getModsInPriorityOrder(QList<Modification*> unordered);

    /**
     * @brief Gets the modification with id
     * @param id
     * @return
     */
    Modification * getModification(const QString & id);

    /**
     * @brief Enables/disables a pipeline
     * @param mod
     * @param content
     * @param enabled
     * @return exitcode
     */
    bool setEnabled(Pipeline * pip, bool enabled, bool prime = true);

    /**
     * @brief Returns true if the pipeline is enabled
     * @param mod
     * @param content
     * @return
     */
    bool isEnabled(Pipeline * pip);

    /**
     * @brief Moves a mod to a higher priority
     * @param mod
     * @return
     */
    bool priotizeUp(Modification * mod);

    /**
     * @brief Moves a mod to a lover priority
     * @param mod
     * @return
     */
    bool priotizeDown(Modification * mod);      

    /**
     * @brief Creates an unique mod-id from the ID
     * @param id
     * @return
     */
    QString unifyModId(QString id);

    /**
     * @brief Returns list of all installed files
     * @return
     */
    QStringList installedFiles();

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
     * @brief Tries to create a mod url from a given file or folder path
     * @param filepath
     * @return
     */
    QString toModUrl(const QString & filepath);

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
    bool importModFromDirectory(const QDir & dir, bool force_overwrite = false, bool interactive = true);

    /**
     * @brief Imports a mod from a *.zip file
     * @param filename
     * @return
     */
    bool importModFromZip(const QString & filename, bool force_overwrite = false, bool interactive = true);

    /**
     * @brief Adds the default mods to the mod list
     * @param force_overwrite
     * @param interactive
     * @return
     */
    bool importDefaultMods(bool force_overwrite = false, bool interactive = true);

    /**
     * @brief Deletes a mod from ID
     * @param modid
     */
    void deleteMod(Modification * mod);

    /**
     * @brief Copies a mod to profile
     * @param modid
     * @param p
     */
    void copyModTo(Modification * mod, Profile * p);

    /**
     * @brief Checks if all dependencies are fulfilled.
     * @param priorityaware
     * @param assumeactivated Assume those pipelines as activated
     * @return Map of modid vs List of unfulfilled dependencies
     */
    QMap<QString, QList<Dependency>> dependencyCheck(bool priorityaware, const QList<Modification*> & modlist);

    /**
     * @brief Gets list of mod paths that could not be loaded
     * @return
     */
    QStringList getUnloadableModPaths() const;

    /**
     * @brief Builds the environment for the executed tools
     * @return
     */
    QProcessEnvironment processEnvironment();

    /**
     * @brief Gets the mod repository
     * @return
     */
    ModRepository *getModRepository() const;

    /**
     * @brief Return the dependency tree
     * @return
     */
    DependencyTree *getDependencyTree() const;

public slots:

    /**
     * @brief Reloads all mods
     */
    void reloadMods();

private:

    ModRepository * m_modRepository;

    QSettings * m_config;

    Profile * m_profile;

    QSet<QString> m_modId;

    QList<Modification*> m_mods;

    QStringList m_unloadableModPaths;

    //Logger m_logger;

    DependencyTree * m_dependencyTree;

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

};

#endif // MODMANAGER_H
