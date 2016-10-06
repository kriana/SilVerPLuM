#include "pipeline.h"
#include "modification.h"
#include "modmanager.h"
#include "platform.h"
#include "launcher.h"
#include "globalsettings.h"
#include "profile.h"
#include "utils.h"

Pipeline::Pipeline(Modification *mod, const QString &id) : m_mod(mod), m_id(id)
{
    connect(mod->getModManager(),
            SIGNAL(modEnabledDisabled(QString,QString,bool)),
            this,
            SLOT(modEnabledDisabled(QString,QString,bool)));
}

void Pipeline::loadGenericFromJson(const QJsonObject &json, Pipeline * pip)
{
    pip->setName(json["name"].toString());
    pip->setDescription(json["description"].toString());
    pip->setPriority(json["priority"].toInt());
    pip->setDefault(json["default"].toBool());

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
            getLogger().log(Logger::WARNING, "pipeline", id(), "resolve-installables", "Refuse to resolve source " + src + " by file guard");

            continue;
        }
        if(dst.contains("..") && GlobalSettings::instance()->getEnableFileGuard())
        {
            getLogger().log(Logger::WARNING, "pipeline", id(), "resolve-installables", "Refuse to resolve source " + src + " by file guard");

            continue;
        }

        if(!QFileInfo(src).exists())
        {
            getLogger().log(Logger::ERROR, "pipeline", id(), "resolve-installables", "Source " + src + " does not exist. Skipping.");

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

                getLogger().log(Logger::WARNING, "pipeline", id(), "resolve-installables-dir", "Resolved " + rsrc + " to " + rdst);

                result[rsrc] = rdst;
            }
        }
        else
        {
            getLogger().log(Logger::WARNING, "pipeline", id(), "resolve-installables-file", "Resolved " + src + " to " + dst);

            result[src] = dst;
        }
    }

    return result;
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
    getLogger().log(Logger::INFO, "pipeline", id(), "install", "Started installation");


    QMap<QString, QString> resolved_installables = resolveInstallables();

    for(QString src : resolved_installables.keys())
    {
        QString dst = resolved_installables[src];

        QDir dst_file_dir = QFileInfo(src).absoluteDir();

        // Prevent overwriting files outside Content dir
        if(QFileInfo(dst).exists() && GlobalSettings::instance()->getEnableFileGuard())
        {
            QDir sdvdir = mod()->getModManager()->profile()->StardewValleyDir();

            if(dst_file_dir == sdvdir ||
                    dst_file_dir == sdvdir.absoluteFilePath("_MACOSX") ||
                    dst_file_dir == sdvdir.absoluteFilePath("lib") ||
                    dst_file_dir == sdvdir.absoluteFilePath("lib64") ||
                    dst_file_dir == sdvdir.absoluteFilePath("mono"))
            {
                getLogger().log(Logger::WARNING, "pipeline", id(), "install", "Refuse to overwrite source " + src + " into " + dst + " by file guard");

                continue;
            }
        }

        // Install
        dst_file_dir.mkpath(".");

        if(QFileInfo(dst).exists())
        {
            if(!QFile(dst).remove())
            {
                getLogger().log(Logger::WARNING, "pipeline", id(), "install", "Could not replace " + dst);
            }
            else
            {
                getLogger().log(Logger::INFO, "pipeline", id(), "install", "Successfully replaced " + dst);
            }
        }

        if(QFile::copy(src, dst))
        {
            getLogger().log(Logger::INFO, "pipeline", id(), "install", "Successfully installed " + src + " to " + dst);
        }
        else
        {
            getLogger().log(Logger::WARNING, "pipeline", id(), "install", "Could not install " + src + " to " + dst);
        }

    }
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

void Pipeline::setEnabled(bool enabled)
{
    m_mod->getModManager()->setEnabled(m_mod->id(), id(), enabled);
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

bool Pipeline::isdefault() const
{
    return m_default;
}

void Pipeline::setDefault(bool isdefault)
{
    m_default = isdefault;
}
