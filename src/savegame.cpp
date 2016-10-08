#include "savegame.h"
#include <QtXml>
#include <QFile>
#include "logger.h"
#include "profile.h"
#include "utils.h"

Savegame::Savegame(const QDir &directory, Profile *p) : m_directory(directory), m_profile(p)
{
    m_settings = new QSettings(directory.absoluteFilePath("SilVerPLuM-info.ini"), QSettings::IniFormat);
}

Profile *Savegame::profile() const
{
    return m_profile;
}

Savegame::~Savegame()
{
    delete m_settings;
}


Savegame *Savegame::loadFromDirectory(const QDir &dir, Profile *profile)
{
    profile->getLogger().log(Logger::INFO, "savegame", "load", "load", "Loading savegame info in " + dir.absolutePath());

    QDomDocument doc;
    QFile file(dir.absoluteFilePath("SaveGameInfo"));

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
    {
        profile->getLogger().log(Logger::ERROR, "savegame", "load", "load", "Could not parse or load SaveGameInfo file");
        return nullptr;
    }

    Savegame * savegame = new Savegame(dir, profile);

    savegame->setName(doc.firstChildElement().firstChildElement("name").firstChild().nodeValue());
    savegame->setFarmName(doc.firstChildElement().firstChildElement("farmName").firstChild().nodeValue());
    savegame->setFavoriteThing(doc.firstChildElement().firstChildElement("favoriteThing").firstChild().nodeValue());
    savegame->setTimedate(doc.firstChildElement().firstChildElement("dateStringForSaveGame").firstChild().nodeValue());
    savegame->setTimePlayedMs(doc.firstChildElement().firstChildElement("millisecondsPlayed").firstChild().nodeValue().toInt());
    savegame->setIsMale(doc.firstChildElement().firstChildElement("isMale").firstChild().nodeValue() == "true");
    savegame->setMoney(doc.firstChildElement().firstChildElement("money").firstChild().nodeValue().toInt());

    return savegame;
}

QString Savegame::name() const
{
    return m_name;
}

void Savegame::setName(const QString &name)
{
    m_name = name;
}

QString Savegame::timedate() const
{
    return m_timedate;
}

void Savegame::setTimedate(const QString &timedate)
{
    m_timedate = timedate;
}

bool Savegame::isMale() const
{
    return m_isMale;
}

void Savegame::setIsMale(bool isMale)
{
    m_isMale = isMale;
}

QString Savegame::farmName() const
{
    return m_farmName;
}

void Savegame::setFarmName(const QString &farmName)
{
    m_farmName = farmName;
}

QString Savegame::favoriteThing() const
{
    return m_favoriteThing;
}

void Savegame::setFavoriteThing(const QString &favoriteThing)
{
    m_favoriteThing = favoriteThing;
}

int Savegame::money() const
{
    return m_money;
}

void Savegame::setMoney(int money)
{
    m_money = money;
}

int Savegame::timePlayedMs() const
{
    return m_timePlayedMs;
}

void Savegame::setTimePlayedMs(int timePlayedMs)
{
    m_timePlayedMs = timePlayedMs;
}

QString Savegame::comment() const
{
    return m_settings->value("Comment", "").toString();
}

void Savegame::setComment(const QString &comment)
{
    m_settings->setValue("Comment", comment);
    m_settings->sync();
}

QDateTime Savegame::backupDate()
{
    QString now_string = QDateTime::currentDateTime().toString("dd-MM-yyyy/HH:mm:ss");
    return QDateTime::fromString(m_settings->value("BackupDate", now_string).toString(), "dd-MM-yyyy/HH:mm:ss");
}

void Savegame::setBackupDate(const QDateTime &datetime)
{
    m_settings->setValue("BackupDate", datetime.toString("dd-MM-yyyy/HH:mm:ss"));
    m_settings->sync();
}

QDir Savegame::directory() const
{
    return m_directory;
}

bool Savegame::contentEquals(Savegame *other) const
{
    return utils::folderEqual(directory(), other->directory());
}

