#include "savegame.h"
#include <QtXml>
#include <QFile>
#include "logger.h"
#include "profile.h"
#include "utils.h"
#include <JlCompress.h>
#include <random>
#include "backupsavegame.h"

Savegame::Savegame(const QDir &directory, Profile *p) : m_directory(directory), m_profile(p)
{
    m_settings = new QSettings(directory.absoluteFilePath("SilVerPLuM-info.ini"), QSettings::IniFormat);
}

QString Savegame::uid() const
{
    return m_uid;
}

void Savegame::setUid(const QString &uid)
{
    m_uid = uid;
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
    profile->getLogger().log(Logger::Info, "savegame", "load", "load", "Loading savegame info in " + dir.absolutePath());

    // Read the savegame info

    QDomDocument doc;
    QFile file(dir.absoluteFilePath("SaveGameInfo"));

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
    {
        profile->getLogger().log(Logger::Error, "savegame", "load", "load", "Could not parse or load SaveGameInfo file");
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


    profile->getLogger().log(Logger::Info, "savegame", "load", "load", "Loading UID");
    // Read the savegame UID
    /*
     * The UID is tricky as the file is EXTREMELY large. DOM won't help here
     *
     * Solution: Datamining -> It is in an element <uniqueIDForThisGame>UID</uniqueIDForThisGame>
     */

    QString datafile;

    for(QString entry : dir.entryList(QDir::Files))
    {
        if(entry.startsWith(savegame->farmerName()) && !entry.endsWith("_old"))
        {
            datafile = dir.absoluteFilePath(entry);
            break;
        }
    }

    if(datafile.isEmpty())
    {
        profile->getLogger().log(Logger::Error, "savegame", "load", "load", "Could not find data file!");
        delete savegame;

        return nullptr;
    }

    profile->getLogger().log(Logger::Info, "savegame", "load", "load", "UID is in " + datafile);

    QString data_content = utils::readAllTextFrom(datafile).replace("\r","").replace("\n", "");

    int uidstart = data_content.indexOf("<uniqueIDForThisGame>");
    int uidend = data_content.indexOf("</uniqueIDForThisGame>");

    if(uidstart < 0 || uidend < 0 || uidend == uidstart || uidend < uidstart)
    {
        profile->getLogger().log(Logger::Error, "savegame", "load", "load", "Could not get UID from data file!");
        delete savegame;

        return nullptr;
    }

    uidstart += QString("<uniqueIDForThisGame>").length();

    QString uid = data_content.mid(uidstart, uidend - uidstart);

    profile->getLogger().log(Logger::Info, "savegame", "load", "load", "UID is " + uid);
    savegame->setUid(uid);

    return savegame;
}

QString Savegame::farmerName() const
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

int Savegame::timePlayedMS() const
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

QString Savegame::generatedDirectoryPrefix()
{
    return m_name.replace(" ", "");
}

QString Savegame::generatedDirectoryName()
{
    return generatedDirectoryPrefix() + "_" + uid();
}

bool Savegame::contentEquals(Savegame *other) const
{
    return utils::folderEqual(directory(), other->directory(), QStringList() << "SilVerPLuM-info.ini");
}

bool Savegame::exportToZip(const QString &path)
{
    QFile(path).remove();

    return JlCompress::compressDir(path, directory().absolutePath(), true);
}

QString Savegame::findNewUID(Profile *profile)
{
    // Need to find a new ID
    QSet<QString> existing_uids = profile->getSavegameManager()->getSavegameUIDs();

    // Use STL random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);

    QString as_uid;

    while(as_uid.isEmpty() || existing_uids.contains(as_uid))
    {
        return QString::number(dis(gen));
    }

    return "";
}

QString Savegame::findNewUID() const
{
    return findNewUID(m_profile);
}

bool Savegame::copyTo(const QDir &dir, bool overwrite)
{
    QString as_uid = uid();

    if(QDir(dir.absoluteFilePath(generatedDirectoryName())).exists())
    {
        if(overwrite)
        {
            QDir(dir.absoluteFilePath(generatedDirectoryName())).removeRecursively();
        }
        else
        {
            as_uid = findNewUID();
        }
    }

    // Now copy
    QString destination = dir.absoluteFilePath(generatedDirectoryPrefix() + "_" + as_uid);

    return copyToAsWithDirName(destination, as_uid);
}

bool Savegame::copyToAsWithDirName(QDir dir, const QString &as_uid)
{
    dir.removeRecursively();

    utils::copyDirectory(directory(), dir.absolutePath(), true);

    if(as_uid != uid())
    {
        QDir dstdir = dir;

        // Fix the filenames
        dstdir.rename(generatedDirectoryName(), generatedDirectoryPrefix() + "_" + as_uid);
        dstdir.rename(generatedDirectoryName() + "_old", generatedDirectoryPrefix() + "_" + as_uid + "_old");

        // Fix the UID
        QString data_content = utils::readAllTextFrom(dstdir.absoluteFilePath(generatedDirectoryPrefix() + "_" + as_uid)).replace("\r","").replace("\n", "");

        data_content = data_content.replace(QString("<uniqueIDForThisGame>%1</uniqueIDForThisGame>").arg(uid()),
                                            QString("<uniqueIDForThisGame>%1</uniqueIDForThisGame>").arg(as_uid));

        QFile datafile(dstdir.absoluteFilePath(generatedDirectoryPrefix() + "_" + as_uid));

        if(datafile.open(QFile::ReadWrite))
        {
            datafile.resize(0);

            QTextStream stream(&datafile);
            stream << data_content;

            datafile.close();

            return true;
        }
        else
        {
            return false;
        }



    }

    return true;
}
