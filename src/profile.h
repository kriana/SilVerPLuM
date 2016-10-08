#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QDir>
#include <QSettings>
#include <QList>
#include <QObject>
#include "launcher.h"
#include "vanillalauncher.h"
#include "modmanager.h"
#include "logger.h"
#include "savegamemanager.h"

class Profile : public QObject
{

    Q_OBJECT

public:

    static QString DEFAULT_PROFILE_NAME;
    static QString DEFAULT_PROFILE_ID;

    Profile(const QString & id);

    ~Profile();    

    QDir profileBaseDir();

    QDir profileSavegameDir();

    QDir profileSavegameBackupDir();

    QDir profileModDir();

    QString id() const;

    void setId(const QString &id);

    QString name() const;

    void setName(const QString & name);

    QString description() const;

    void setDescription(const QString & desc);

    QDir StardewValleyDir();

    void setStardewValleyDir(const QDir & dir);

    QDir StardewValleySavegameDir();

    void setStardewValleySavegameDir(const QDir & dir);

    QVersionNumber StardewValleyVersion();

    void setStardewValleyVersion(const QVersionNumber & version);

    bool exists();

    void setLauncher(const QString & id);

    Launcher * getLauncher();

    Launcher * getLauncher(const QString & id);

    QList<Launcher*> getLaunchers();

    void initialize();

public slots:

    void repairDirectories();

private:

    QString m_Id;

    QSettings * m_Settings;

    QList<Launcher *> m_Launchers;

    ModManager * m_modManager;

    SavegameManager * m_savegameManager;

    Logger m_logger;

signals:

    void updated();

public:

    /**
     * @brief Platform-specific locations for Stardew Valley savegames
     * @return
     */
    static QDir DefaultStardewValleySavegameDir();

    /**
     * @brief Platform-specific locations for Stardew Valley
     * @return
     */
    static QDir DefaultStardewValleyDir();

    ModManager *getModManager() const;

    Logger & getLogger();

    SavegameManager *getSavegameManager() const;
};

#endif // PROFILE_H
