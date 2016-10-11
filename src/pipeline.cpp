#include "pipeline.h"
#include "modification.h"
#include "modmanager.h"
#include "platform.h"
#include "launcher.h"
#include "globalsettings.h"
#include "profile.h"
#include "utils.h"
#include "game.h"
#include "quazipcompress.h"

Pipeline::Pipeline(Modification *mod, const QString &id) : m_mod(mod), m_id(id)
{
    connect(mod->getModManager(),
            SIGNAL(updatedModStatus(QString,QString,bool)),
            this,
            SLOT(modEnabledDisabled(QString,QString,bool)));
}

bool Pipeline::loadGenericFromJson(const QJsonObject &json, Pipeline * pip)
{
    pip->setName(json["name"].toString());
    pip->setDescription(json["description"].toString());
    pip->setPriority(json["priority"].toInt());
    pip->setDefault(json["default"].toBool());

    // Additional way of description
    QString alternate_descr_file = pip->pipelineBaseDir().absoluteFilePath("mod-description.md");
    if(QFileInfo(alternate_descr_file).exists())
    {
        pip->setDescription(utils::readAllTextFrom(alternate_descr_file));
    }

    QJsonObject installables = json["installables"].toObject();

    for(QString src : installables.keys())
    {
        QString dst = installables[src].toString();

        pip->setInstallable(src, dst);
    }

    bool platform_found = false;

    for(QJsonValue supported : json["platforms"].toArray())
    {
        if(supported.toString() == Platform::getPlatformString())
        {
            platform_found = true;
        }
    }

    pip->setUnsupported(!platform_found);

    QJsonObject launcher_map = json["launchers"].toObject();

    for(QString id : launcher_map.keys())
    {
        Launcher * launcher = Launcher::loadFromJson(pip->mod()->getModManager()->profile(),
                                                     pip,
                                                     id,
                                                     launcher_map[id].toObject());
        pip->setLauncher(id, launcher);
    }

    QJsonObject encrypted_map = json["encrypted-content"].toObject();

    for(QString zipfile : encrypted_map.keys())
    {
        EncryptionEntry entry;
        entry.zipfile = zipfile;
        entry.password = encrypted_map[zipfile].toObject()["password"].toString();
        entry.destination = encrypted_map[zipfile].toObject()["destination"].toString();

        for(QJsonValue val : encrypted_map[zipfile].toObject()["keep"].toArray())
        {
            entry.keep << val.toString();
        }

        if(GlobalSettings::instance()->getEnableFileGuard())
        {
            if(entry.zipfile.contains("..") || entry.destination.contains(".."))
            {
                pip->getLogger().log(Logger::Warning, "pipeline", pip->id(), "load", "Refuse to load encrypted entry " + zipfile + " by file guard");
                continue;
            }
        }

        pip->addEncryptionEntry(entry);
    }

    return true;
}

QMap<QString, QString> Pipeline::resolveInstallables()
{
    QMap<QString, QString> result;

    for(const QString & key : m_installables.keys())
    {
        QString dst = mod()->getModManager()->profile()->StardewValleyDir().absolutePath() + "/" + m_installables[key];
        QString src = pipelineBaseDir().absolutePath() + "/" + key;

        // Prevent breaking out of the directories via ..
        if(src.contains("..") && GlobalSettings::instance()->getEnableFileGuard())
        {
            getLogger().log(Logger::Warning, "pipeline", id(), "resolve-installables", "Refuse to resolve source " + src + " by file guard");

            continue;
        }
        if(dst.contains("..") && GlobalSettings::instance()->getEnableFileGuard())
        {
            getLogger().log(Logger::Warning, "pipeline", id(), "resolve-installables", "Refuse to resolve source " + src + " by file guard");

            continue;
        }

        if(!QFileInfo(src).exists())
        {
            getLogger().log(Logger::Error, "pipeline", id(), "resolve-installables", "Source " + src + " does not exist. Skipping.");

            continue;
        }

        // If it's a directory, resolve it to files; otherwise just add them
        if(QFileInfo(src).isDir())
        {
            for(QString rsrc : utils::findAllFiles(src))
            {
                /*
                 * key : Content
                 * src : /home/user/..../testmod/content/Content
                 * rsrc : /home/user/..../testmod/content/Content/Portraits/Abigail.xnb
                 */

                QString rdst = dst + "/" + rsrc.mid(src.length());
                rsrc = QFileInfo(rsrc).canonicalFilePath();
                rdst = QFileInfo(rdst).exists() ? QFileInfo(rdst).canonicalFilePath() : rdst;

                getLogger().log(Logger::Info, "pipeline", id(), "resolve-installables-dir", "Resolved " + rsrc + " to " + rdst);

                result[rsrc] = rdst;
            }
        }
        else
        {
            src = QFileInfo(src).canonicalFilePath();
            dst = QFileInfo(dst).exists() ? QFileInfo(dst).canonicalFilePath() : dst;

            getLogger().log(Logger::Info, "pipeline", id(), "resolve-installables-file", "Resolved " + src + " to " + dst);

            result[src] = dst;
        }
    }

    return result;
}

bool Pipeline::alreadyPrimed()
{
    return true;
}

QList<Pipeline::EncryptionEntry> Pipeline::getEncryptionEntries() const
{
    return QList<EncryptionEntry>(m_encryptionEntries);
}

void Pipeline::addEncryptionEntry(const Pipeline::EncryptionEntry &entry)
{
    m_encryptionEntries << entry;
}

Pipeline *Pipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    Pipeline * pip = new Pipeline(mod, id);

        if(!loadGenericFromJson(json, pip))
        {
            delete pip;
            return nullptr;
        }

    return pip;
}

Logger &Pipeline::getLogger()
{
    return m_logger;
}

QList<Launcher *> Pipeline::launchers() const
{
    return m_launchers.values();
}

void Pipeline::install()
{
    getLogger().log(Logger::Info, "pipeline", id(), "install", "Started installation");

    m_fgInstalledFiles.clear();
    QMap<QString, QString> resolved_installables = resolveInstallables();

    for(QString src : resolved_installables.keys())
    {
        QString dst = resolved_installables[src];

        QDir dst_file_dir = QFileInfo(dst).absoluteDir();

        // Prevent overwriting files outside Content dir
        if(QFileInfo(dst).exists() && GlobalSettings::instance()->getEnableFileGuard())
        {
            QDir sdvdir = mod()->getModManager()->profile()->StardewValleyDir();

            //getLogger().log(Logger::DEBUG, "pipeline", id(), "install", dst_file_dir.absolutePath() + " == " + sdvdir.absolutePath());

            /*if(dst_file_dir.absolutePath() == sdvdir.absolutePath() ||
                    dst_file_dir.absolutePath() == QDir(sdvdir.absoluteFilePath("_MACOSX")).absolutePath() ||
                    dst_file_dir.absolutePath() == QDir(sdvdir.absoluteFilePath("lib")).absolutePath() ||
                    dst_file_dir.absolutePath() == QDir(sdvdir.absoluteFilePath("lib64")).absolutePath() ||
                    dst_file_dir.absolutePath() == QDir(sdvdir.absoluteFilePath("mono")).absolutePath())
            {
                getLogger().log(Logger::Warning, "pipeline", id(), "install", "Refuse to overwrite source " + src + " into " + dst + " by file guard");

                continue;
            }*/

            if(Game::instance()->getUnoverrideableGameFiles().contains(dst_file_dir.absolutePath()))
            {
                getLogger().log(Logger::Warning, "pipeline", id(), "install", "Refuse to overwrite source " + src + " into " + dst + " by file guard");

                continue;
            }

        }

        // Install
        dst_file_dir.mkpath(".");

        if(QFileInfo(dst).exists())
        {
            if(!QFile(dst).remove())
            {
                getLogger().log(Logger::Warning, "pipeline", id(), "install", "Could not replace " + dst);
            }
            else
            {
                getLogger().log(Logger::Info, "pipeline", id(), "install", "Successfully replaced " + dst);
            }
        }

        if(QFile::copy(src, dst))
        {
            getLogger().log(Logger::Info, "pipeline", id(), "install", "Successfully installed " + src + " to " + dst);
        }
        else
        {
            getLogger().log(Logger::Warning, "pipeline", id(), "install", "Could not install " + src + " to " + dst);
        }

        m_fgInstalledFiles.insert(dst); // Mark as installed

    }
}

void Pipeline::uninstall()
{
    getLogger().log(Logger::Info, "pipeline", id(), "uninstall", "Started uninstallation");

    for(QString dst : m_fgInstalledFiles)
    {
        if(QFile(dst).remove())
        {
            getLogger().log(Logger::Info, "pipeline", id(), "uninstall", "Successfully uninstalled " + dst);
        }
        else
        {
            getLogger().log(Logger::Warning, "pipeline", id(), "uninstall", "Could not uninstall " + dst);
        }
    }

    m_fgInstalledFiles.clear();
}

bool Pipeline::unsupported() const
{
    return m_unsupported;
}

void Pipeline::setUnsupported(bool unsupported)
{
    m_unsupported = unsupported;
}

bool Pipeline::search(const QString &searchstring_)
{
    QString searchstring = searchstring_.toLower();

    return name().toLower().contains(searchstring) ||
            description().toLower().contains(searchstring) ||
            id().toLower().contains(searchstring);
}

void Pipeline::modEnabledDisabled(const QString &modid, const QString &contentid, bool enabled)
{
    if(modid == m_mod->id() && contentid == m_id)
    {
        emit contentEnabledDisabled(enabled);
    }
}

QString Pipeline::id() const
{
    return m_id;
}

bool Pipeline::isEnabled()
{
    return m_mod->getModManager()->isEnabled(m_mod->id(), id());
}

int Pipeline::setEnabled(bool enabled)
{
    return m_mod->getModManager()->setEnabled(m_mod->id(), id(), enabled);
}

QDir Pipeline::pipelineBaseDir()
{
    return m_mod->modBasePath().absoluteFilePath(id());
}

Pipeline::~Pipeline()
{

}

QString Pipeline::name() const
{
    return m_name;
}

void Pipeline::setName(const QString &name)
{
    m_name = name;
}

QString Pipeline::description() const
{
    return m_description;
}

void Pipeline::setDescription(const QString &description)
{
    m_description = description;
}

int Pipeline::priority() const
{
    return m_priority;
}

void Pipeline::setPriority(int priority)
{
    m_priority = priority;
}

Modification *Pipeline::mod() const
{
    return m_mod;
}

void Pipeline::setInstallable(const QString &src, const QString &dst)
{
    m_installables[src] = dst;
}

void Pipeline::setLauncher(const QString &id, Launcher *launcher)
{
    m_launchers[id] = launcher;
}

int Pipeline::primePipeline(bool force)
{
    if(!force && alreadyPrimed())
        return 0;

    int ret = 0;

    QStringList keep_encryped_raw;
    QStringList extracted;

    for(const EncryptionEntry & entry : m_encryptionEntries)
    {
        for(QString keep : entry.keep)
        {
            keep_encryped_raw << pipelineBaseDir().absolutePath() + "/" + keep;
        }
    }

    // Extract encrypted files
    for(const EncryptionEntry & entry : m_encryptionEntries)
    {
        QString zipfile = pipelineBaseDir().absolutePath() + "/" + entry.zipfile;
        QString destination = pipelineBaseDir().absolutePath() + "/" + entry.destination;

        QDir(destination).mkpath(".");

        QString pw = utils::encryptedContentDecryptPassword(entry.password);


        QStringList extracted_here = QuazipCompress::extractDir(zipfile, destination, pw);
        extracted << extracted_here;

        if(extracted_here.isEmpty())
        {
            ret = 2;
            break;
        }
    }

    // Prime
    if(ret == 0)
    {
        ret = prime();
    }
    else
    {
        getLogger().log(Logger::Error, "pipeline-prime", id(), "prime", "Could not extract encrypted folders!");
    }

    // Resolve kept files
    QStringList keep;

    for(QString file : keep_encryped_raw)
    {
        if(QFileInfo(file).exists())
        {
            if(QFileInfo(file).isFile())
            {
                keep << QFileInfo(file).canonicalFilePath();
            }
            else
            {
                for(QString f : utils::findAllFiles(file))
                {
                    keep << QFileInfo(f).canonicalFilePath();
                }
            }
        }
    }

    // Delete encryped files
    for(QString file : extracted)
    {
        if(QFileInfo(file).exists())
        {
            if(keep.contains(QFileInfo(file).canonicalFilePath()))
            {
                continue;
            }
            else
            {
                QFile(file).remove();
            }
        }
    }

    return ret;
}

int Pipeline::prime()
{
    return 0;
}

bool Pipeline::isdefault() const
{
    return m_default;
}

void Pipeline::setDefault(bool isdefault)
{
    m_default = isdefault;
}
