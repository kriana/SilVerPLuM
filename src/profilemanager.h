#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QList>
#include <QObject>
#include "profile.h"
#include "logger.h"

class ProfileManager : public QObject
{  
    Q_OBJECT

public:

    static ProfileManager * instance();

    ~ProfileManager();

private:

    static ProfileManager * m_pInstance;

    ProfileManager();    

    QList<Profile *> m_Profiles;

    Profile * m_SelectedProfile = nullptr;

    Logger m_logger;

    bool m_initialized = false;

public:

    /**
     * @brief Initializes this manager
     */
    void initialize();

    /**
     * @brief Gets the list of all profiles
     * @return
     */
    QList<Profile *> getProfiles();

    /**
     * @brief Gets a profile from ID
     * @param id
     * @return
     */
    Profile * getProfile(const QString &id);

    /**
     * @brief Creates or loads a profile with name
     * @param name
     * @return
     */
    Profile *createOrLoadProfile(const QString & name);

    /**
     * @brief Creates or loads a profile with name and id
     * @param id
     * @param name
     * @return
     */
    Profile *createOrLoadProfile(const QString & id, const QString & name);

    /**
     * @brief Deletes a profile
     * @param p
     * @return
     */
    bool deleteProfile(Profile * p);

    /**
     * @brief Duplicates profile with new name
     * @param p
     * @param name
     * @return
     */
    bool duplicateProfile(Profile * p, const QString & name);

    /**
     * @brief Exports profile into *.zip
     * @param p
     * @param path
     * @return
     */
    bool exportProfile(Profile * p, const QString & path);

    /**
     * @brief Imports profile to *.zip with new name
     * @param path
     * @param name
     * @return
     */
    bool importProfile(const QString & path, const QString &name);

    /**
     * @brief Returns true if a profile with ID exists
     * @param id
     * @return
     */
    bool idExists(const QString & id);

    /**
     * @brief Returns the directory where the profiles are stored
     * @return
     */
    static QDir ProfilesDir();

    /**
     * @brief Returns the currently selected profile
     * @return
     */
    Profile * getSelectedProfile();

    /**
     * @brief Selects a profile
     * @param p
     */
    void selectProfile(Profile * p);

    /**
     * @brief Returns the logger
     * @return
     */
    Logger &getLogger();

signals:

    void updated();

    void updatedProfileSetting();

    void updatedProfileList();

    void updatedSelection(Profile * p);

};

#endif // PROFILEMANAGER_H
