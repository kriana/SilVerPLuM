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
    ModManager(Profile * profile);

    ~ModManager();

    Profile *profile() const;

    void initialize();

    QList<Modification*> getModifications();

    Modification * getModification(const QString & id);

    Pipeline * getPipeline(const QString & mod, const QString & content);

    void setEnabled(const QString & mod, const QString & content, bool enabled);

    bool isEnabled(const QString & mod, const QString & content);

    bool priotizeUp(const QString & mod);

    bool priotizeDown(const QString & mod);

    bool dependencySatisfied(const Dependency & dep, Modification *requester, bool priorityaware);

    QMap<QString, QList<Dependency> > getUnsatisfiedDependencies() const;

    void install();

    /**
     * @brief Resolves mod file paths like modid://file
     * @param url
     * @return
     */
    QString resolveModUrl(const QString & url);

    Logger & getLogger();

    void addMod(const QString & filename);

    void deleteMod(const QString & modid);

public slots:

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

    void loadMod(const QDir & directory);

    void loadMods();

    void sortMods();

signals:

    void modListUpdated();

    void modEnabledDisabled(const QString & modid, const QString & contentid, bool enabled);

    void dependencyCheckFinished();

};

#endif // MODMANAGER_H
