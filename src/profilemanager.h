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

    void initialize();

    QList<Profile *> getProfiles();

    Profile * getProfile(const QString &id);

    Profile *createOrLoadProfile(const QString & name);

    Profile *createOrLoadProfile(const QString & id, const QString & name);

    void deleteProfile(Profile * p);

    void duplicateProfile(Profile * p, const QString & name);

    void exportProfile(Profile * p, const QString & path);

    void importProfile(const QString & path, const QString &name);

    bool idExists(const QString & id);

    static QDir ProfilesDir();

    Profile * getSelectedProfile();

    void selectProfile(Profile * p);

    Logger &getLogger();

signals:

    void updated();

    void updatedProfileSetting();

    void updatedProfileList();

    void updatedSelection(Profile * p);

};

#endif // PROFILEMANAGER_H
