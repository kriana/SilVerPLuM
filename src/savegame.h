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

    QString name() const;
    void setName(const QString &name);

    QString timedate() const;
    void setTimedate(const QString &timedate);

    bool isMale() const;
    void setIsMale(bool isMale);

    QString farmName() const;
    void setFarmName(const QString &farmName);

    QString favoriteThing() const;
    void setFavoriteThing(const QString &favoriteThing);

    int money() const;
    void setMoney(int money);

    int timePlayedMs() const;
    void setTimePlayedMs(int timePlayedMs);

    QString comment() const;
    void setComment(const QString &comment);  

    QDateTime backupDate();
    void setBackupDate(const QDateTime & datetime);

    QDir directory() const;

    Profile *profile() const;

protected:

    Savegame(const QDir & directory, Profile * p);

private:

    QDir m_directory;

    Profile * m_profile;

    QString m_name;

    QString m_timedate;

    bool m_isMale;

    QString m_farmName;

    QString m_favoriteThing;

    int m_money;

    int m_timePlayedMs;

    QSettings *m_settings = nullptr;

};

#endif // SAVEGAME_H
