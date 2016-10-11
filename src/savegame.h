#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <QString>
#include <QDir>
#include <QSettings>
#include <QDateTime>
#include "logger.h"

class Profile;

class Savegame
{
public:

    ~Savegame();

    static Savegame *loadFromDirectory(const QDir & dir, Profile * profile);

    QString uid() const;

    QString name() const;

    QString timedate() const;

    bool isMale() const;

    QString farmName() const;

    QString favoriteThing() const;

    int money() const;

    int timePlayedMs() const;

    QString comment() const;

    void setComment(const QString &comment);

    QDateTime backupDate();

    void setBackupDate(const QDateTime & datetime);

    QDir directory() const;

    QString generatedDirectoryPrefix();

    QString generatedDirectoryName();

    Profile *profile() const;

    QString findNewUID() const;

    static QString findNewUID(Profile * profile);

    /**
     * @brief Copies this savegame to directory. If overwrite is not set, it will rename this savegame if needed
     * @param dir
     * @param overwrite
     * @return
     */
    bool copyTo(const QDir & dir, bool overwrite);

    bool copyToAsWithDirName(QDir dir, const QString & as_uid);

    /**
     * @brief Returns true if this and the other savegame have the same content
     * @return
     */
    bool contentEquals(Savegame * other) const;

    /**
     * @brief Exports this savegame to a *.zip file
     * @param path
     */
    bool exportToZip(const QString & path);


protected:

    Savegame(const QDir & directory, Profile * p);

private:

    QDir m_directory;

    Profile * m_profile;

    QString m_uid;

    QString m_name;

    QString m_timedate;

    bool m_isMale;

    QString m_farmName;

    QString m_favoriteThing;

    int m_money;

    int m_timePlayedMs;

    QSettings *m_settings = nullptr;

    void setName(const QString &name);
    void setTimedate(const QString &timedate);
    void setIsMale(bool isMale);
    void setFarmName(const QString &farmName);
    void setFavoriteThing(const QString &favoriteThing);
    void setMoney(int money);
    void setTimePlayedMs(int timePlayedMs);
    void setUid(const QString &uid);

};

#endif // SAVEGAME_H
