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

    /**
     * @brief Loads a savegame from a directory
     * @param dir
     * @param profile
     * @return
     */
    static Savegame *loadFromDirectory(const QDir & dir, Profile * profile);

    /**
     * @brief UID of this savegame
     * @return
     */
    QString uid() const;

    /**
     * @brief Farmer name of this savegame
     * @return
     */
    QString farmerName() const;

    /**
     * @brief The ingame date & time
     * @return
     */
    QString timedate() const;

    /**
     * @brief Returns true if the farmer is male
     * @return
     */
    bool isMale() const;

    /**
     * @brief Returns the farm name
     * @return
     */
    QString farmName() const;

    /**
     * @brief Returns the favorite thing of the farmer
     * @return
     */
    QString favoriteThing() const;

    /**
     * @brief Return the farmer's money
     * @return
     */
    int money() const;

    /**
     * @brief Returns milliseconds the user played this savegame
     * @return
     */
    int timePlayedMS() const;

    /**
     * @brief Disfunctional
     * @return
     */
    QString comment() const;

    /**
     * @brief Disfunctional
     * @param comment
     */
    void setComment(const QString &comment);

    /**
     * @brief Returns the backup date
     * @return
     */
    QDateTime backupDate();

    /**
     * @brief Sets the backup date
     * @param datetime
     */
    void setBackupDate(const QDateTime & datetime);

    /**
     * @brief Returns the directory of the savegame
     * @return
     */
    QDir directory() const;

    /**
     * @brief Returns the prefix of the savegame which is FarmerName, but modified
     * @return
     */
    QString generatedDirectoryPrefix();

    /**
     * @brief Get the name of the directory of this savegame. This is not the actual directory name, but the name usable by the game
     * @return
     */
    QString generatedDirectoryName();

    /**
     * @brief Gets the profile
     * @return
     */
    Profile *profile() const;

    /**
     * @brief Finds a new UID for this savegame
     * @return
     */
    QString findNewUID() const;

    /**
     * @brief Finds a new UID for a savegame in profile
     * @param profile
     * @return
     */
    static QString findNewUID(Profile * profile);

    /**
     * @brief Copies this savegame to directory. If overwrite is not set, it will rename this savegame if needed
     * @param dir
     * @param overwrite
     * @return
     */
    bool copyTo(const QDir & dir, bool overwrite);

    /**
     * @brief Copies the savegame into directory with renaming UID
     * @param dir
     * @param as_uid
     * @return
     */
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

    void setName(const QString &farmerName);
    void setTimedate(const QString &timedate);
    void setIsMale(bool isMale);
    void setFarmName(const QString &farmName);
    void setFavoriteThing(const QString &favoriteThing);
    void setMoney(int money);
    void setTimePlayedMs(int timePlayedMS);
    void setUid(const QString &uid);

};

#endif // SAVEGAME_H
