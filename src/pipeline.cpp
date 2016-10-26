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

    // Post prime copy
    QMap<QString, QString> postprime_copy_result;
    QJsonObject postprime_copy_map = json["postprime-copy"].toObject();

    for(QString src : postprime_copy_map.keys())
    {
        QString dst = postprime_copy_map[src].toString();
        postprime_copy_result[src] = dst;
    }

    pip->setPostprimeCopy(postprime_copy_result);

    // Provides identifiers
    QStringList provides;

    for(QJsonValue prov : json["provides"].toArray())
    {
        if(utils::isValidModId(prov.toString()))
        {
            provides << prov.toString();
        }
        else
        {
            pip->getLogger().log(Logger::Error, "pipeline", pip->id(), "load", "Refusing provides " + prov.toString() + ": same rules as pipeline-id");
        }
    }

    pip->setProvides(provides);

    return true;
}

QMap<QString, QString> Pipeline::resolveInstallables(const QMap<QString, QString> &input, const QString & default_destination, QMap<QString, QString> *destinationsources)
{
    QMap<QString, QString> result;

    for(const QString & key : input.keys())
    {
        QString dst = input[key];

        // New addition: Support mod URLs
        if(mod()->getModManager()->isValidModUrl(dst))
        {
            dst = mod()->getModManager()->resolveModUrl(dst);
        }
        else
        {
            getLogger().log(Logger::Warning, "pipeline", id(), "resolve-installables", "No valid mod URL in installable. Assuming default.");

            /*
             * Support content dir override
             */
            if(dst == "Content")
            {
                getLogger().log(Logger::Warning, "pipeline", id(), "resolve-installables", "Content directory detected. Please use stardewvalley-content://");

                dst = mod()->getModManager()->profile()->StardewValleyContentDir().absolutePath();
            }
            else if(dst.startsWith("Content/"))
            {
                getLogger().log(Logger::Warning, "pipeline", id(), "resolve-installables", "Content directory detected. Please use stardewvalley-content://");

                dst = dst.replace("Content/", mod()->getModManager()->profile()->StardewValleyContentDir().absolutePath() + "/");
            }
            else
            {
                dst = default_destination + "/" + dst;
            }
        }

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

                //QString rdst = dst + "/" + rsrc.mid(src.length());
                QString rdst = dst + "/" + QDir(src).relativeFilePath(rsrc);
                rsrc = QFileInfo(rsrc).canonicalFilePath();
                rdst = QFileInfo(rdst).exists() ? QFileInfo(rdst).canonicalFilePath() : rdst;

                getLogger().log(Logger::Info, "pipeline", id(), "resolve-installables-dir", "Resolved " + rsrc + " to " + rdst);

                result[rsrc] = rdst;

                if(destinationsources != nullptr)
                {
                    destinationsources->insert(rdst, key);
                }
            }
        }
        else
        {
            src = QFileInfo(src).canonicalFilePath();
            dst = QFileInfo(dst).exists() ? QFileInfo(dst).canonicalFilePath() : dst;

            getLogger().log(Logger::Info, "pipeline", id(), "resolve-installables-file", "Resolved " + src + " to " + dst);

            result[src] = dst;

            if(destinationsources != nullptr)
            {
                destinationsources->insert(dst, key);
            }
        }
    }

    // Post-resolve content
    for(QString src : result.keys())
    {
        QString dst = result[src];

        if(dst.startsWith(mod()->getModManager()->profile()->StardewValleyDir().absoluteFilePath("Content") + "/"))
        {
            QString ndst = dst.replace(mod()->getModManager()->profile()->StardewValleyDir().absoluteFilePath("Content") + "/",
                                       mod()->getModManager()->profile()->StardewValleyContentDir().absolutePath());
            if(dst != ndst)
            {
                getLogger().log(Logger::Info, "pipeline", id(), "resolve-installables-post-contentfix", "Resolved for " + src + " destination from " + dst + " to " + ndst);
                result[src] = ndst;
            }
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
    return m_mod->getLogger();
}

QList<Launcher *> Pipeline::launchers() const
{
    return m_launchers.values();
}

QStringList Pipeline::installedFiles()
{
    QMap<QString, QString> resolved_installables = resolveInstallables(m_installables, m_mod->getModManager()->profile()->StardewValleyDir().absolutePath());

    return resolved_installables.values();
}

void Pipeline::install()
{
    getLogger().log(Logger::Info, "pipeline", id(), "install", "Started installation");

    m_fgInstalledFiles.clear();
    QMap<QString, QString> resolved_installables = resolveInstallables(m_installables, m_mod->getModManager()->profile()->StardewValleyDir().absolutePath());

    for(QString src : resolved_installables.keys())
    {
        QString dst = resolved_installables[src];

        QDir dst_file_dir = QFileInfo(dst).absoluteDir();

        // Prevent overwriting files outside Content dir
        if(QFileInfo(dst).exists() && GlobalSettings::instance()->getEnableFileGuard())
        {
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

QString Pipeline::pipelineType() const
{
    return "file";
}

bool Pipeline::isEnabled()
{
    return m_mod->getModManager()->isEnabled(this);
}

int Pipeline::setEnabled(bool enabled, bool prime)
{
    return m_mod->getModManager()->setEnabled(this, enabled);
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
    QString ssrc = src;
    QString sdst = dst;
    m_installables[ssrc.replace("\\","/")] = sdst.replace("\\","/");
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
        ret = prime(force);
    }
    else
    {
        getLogger().log(Logger::Error, "pipeline-prime", id(), "prime", "Could not extract encrypted folders!");
    }

    // Post-prime copy
    postprimeCopy();

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

int Pipeline::prime(bool is_forced)
{
    return 0;
}

void Pipeline::postprimeCopy()
{
    getLogger().log(Logger::Info, "pipeline", id(), "postprime-copy", "Started");

    QMap<QString, QString> resolved_installables = resolveInstallables(m_postprimeCopy, pipelineBaseDir().absolutePath());

    for(QString src : resolved_installables.keys())
    {
        QString dst = resolved_installables[src];

        QDir dst_file_dir = QFileInfo(dst).absoluteDir();

        // Install
        dst_file_dir.mkpath(".");

        if(QFileInfo(dst).exists())
        {
            if(!QFile(dst).remove())
            {
                getLogger().log(Logger::Warning, "pipeline", id(), "postprime-copy", "Could not replace " + dst);
            }
            else
            {
                getLogger().log(Logger::Info, "pipeline", id(), "postprime-copy", "Successfully replaced " + dst);
            }
        }

        if(QFile::copy(src, dst))
        {
            getLogger().log(Logger::Info, "pipeline", id(), "postprime-copy", "Successfully copied " + src + " to " + dst);
        }
        else
        {
            getLogger().log(Logger::Warning, "pipeline", id(), "postprime-copy", "Could not copied " + src + " to " + dst);
        }
    }
}

QMap<QString, QString> Pipeline::getPostprimeCopy() const
{
    return m_postprimeCopy;
}

void Pipeline::setPostprimeCopy(const QMap<QString, QString> &postprimeCopy)
{
    m_postprimeCopy = postprimeCopy;
}

QStringList Pipeline::getProvides() const
{
    return m_provides;
}

void Pipeline::setProvides(const QStringList &provides)
{
    m_provides = provides;
}

QProcessEnvironment Pipeline::processEnvironment()
{
    QProcessEnvironment env = mod()->processEnvironment();

    env.insert("SILVERPLUM_CURRENT_PIPELINE_DIR", pipelineBaseDir().absolutePath());
    env.insert("SILVERPLUM_CURRENT_PIPELINE_TYPE", pipelineType());

    return env;
}

int Pipeline::runProgram()
{
    return 0;
}

QStringList Pipeline::repositories()
{
    return QStringList();
}

Pipeline::PipelineType Pipeline::pipelineMainType() const
{
    return ContentPipeline;
}

bool Pipeline::isdefault() const
{
    return m_default;
}

void Pipeline::setDefault(bool isdefault)
{
    m_default = isdefault;
}


