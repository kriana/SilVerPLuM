#include "modification.h"
#include "modmanager.h"
#include "profile.h"
#include <QDebug>
#include <QRegExp>
#include "dllpipeline.h"
#include "custompipeline.h"
#include "globalsettings.h"
#include "utils.h"
#include <JlCompress.h>

QDir Modification::modBasePath() const
{
    return m_modBasePath;
}

void Modification::setModBasePath(const QDir &modBasePath)
{
    m_modBasePath = modBasePath;
}

Logger &Modification::getLogger()
{
    return m_logger;
}

bool Modification::exportToZip(const QString &path)
{
    QFile(path).remove();

    return JlCompress::compressDir(path, modBasePath().absolutePath(), true);
}

QStringList Modification::getProvides() const
{
    return m_provides;
}

void Modification::setProvides(const QStringList &provides)
{
    m_provides = provides;
}

QProcessEnvironment Modification::processEnvironment()
{
    QProcessEnvironment env = getModManager()->processEnvironment();

    env.insert("SILVERPLUM_CURRENT_MOD_DIR", modBasePath().absolutePath());

    return env;
}

Modification::Modification(ModManager *modmgr, const QString &id) : m_modManager(modmgr), m_Id(id)
{
    connect(modmgr, SIGNAL(updatedModStatus(QString,QString,bool)), this, SLOT(modEnabledDisabled(QString,QString,bool)));
}

Modification::~Modification()
{
    for(Dependency * dep : m_Dependencies)
    {
        delete dep;
    }

    for(Pipeline * p : m_Pipelines)
    {
        p->deleteLater();
    }
}


QString Modification::author() const
{
    return m_Author;
}

void Modification::setAuthor(const QString &Author)
{
    m_Author = Author;
}

QString Modification::url() const
{
    return m_Url;
}

void Modification::setUrl(const QString &Url)
{
    m_Url = Url;
}

QString Modification::license() const
{
    return m_License;
}

void Modification::setLicense(const QString &License)
{
    m_License = License;
}

bool Modification::isPartiallyEnabled()
{
    for(Pipeline * p : m_Pipelines)
    {
        if(p->isEnabled())
        {
            return true;
        }
    }

    return false;
}

QList<Pipeline *> Modification::getEnabledPipelines()
{
    QList<Pipeline*> result;

    for(Pipeline * p : m_Pipelines) //Pipelines are sorted by priority
    {
        if(p->isEnabled())
            result << p;
    }

    return result;
}

bool Modification::search(const QString &searchstring_)
{
    QString searchstring = searchstring_.toLower();

    if(name().toLower().contains(searchstring) ||
            description().toLower().contains(searchstring) ||
            id().toLower().contains(searchstring) ||
            author().toLower().contains(searchstring) ||
            version().toString().toLower().contains(searchstring) ||
            license().toLower().contains(searchstring) ||
            url().toLower().contains(searchstring))
    {
        return true;
    }

    for(Pipeline * p : m_Pipelines)
    {
        if(p->search(searchstring))
            return true;
    }

    return false;
}

void Modification::install()
{
    for(Pipeline * p : getEnabledPipelines())
    {
        p->install();
    }
}

void Modification::uninstall()
{
    for(Pipeline * p : getEnabledPipelines())
    {
        p->uninstall();
    }
}

int Modification::prime(bool force)
{
    int err = 0;

    for(Pipeline * p : getEnabledPipelines())
    {
        if(p->isEnabled())
        {
            if(!p->unsupported() || GlobalSettings::instance()->getForceUnsupported())
            {
                int e = p->primePipeline(force);

                if(e != 0)
                    err = e;
            }
        }
    }

    return err;
}

void Modification::modEnabledDisabled(const QString &modid, const QString &contentid, bool enabled)
{
    if(modid == id())
    {
        emit contentEnabledDisabled(contentid, enabled);
    }
}

Modification * Modification::loadFromJson(ModManager * modmgr, const QDir & basepath, const QJsonObject &json)
{
    QString id = json["id"].toString().trimmed();

    if(ModManager::FORBIDDEN_MOD_IDS.contains(id))
    {
        modmgr->getLogger().log(Logger::Error, "modification", id, "load", "Mods with id 'stardewvalley' are forbidden. Skipping mod in " + basepath.absolutePath());
        return nullptr;
    }   
    if(!utils::isValidModId(id))
    {
        modmgr->getLogger().log(Logger::Error, "modification", id, "load", "Mod IDs must be alphanumeric with additional chars '.', '-' and '_'. Skipping mod in " + basepath.absolutePath());

        return nullptr;
    }    

    Modification * mod = new Modification(modmgr, id);

    mod->setModBasePath(basepath);
    mod->setName(json["name"].toString());
    mod->setDescription(json["description"].toString());
    mod->setAuthor(json["author"].toString());
    mod->setUrl(json["url"].toString());
    mod->setLicense(json["license"].toString());
    mod->setVersion(QVersionNumber::fromString(json["version"].toString()));

    for(QJsonValue req : json["requires"].toArray())
    {
        mod->addDependency(new Dependency(req.toString()));
    }

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
            modmgr->getLogger().log(Logger::Error, "modification", id, "load", "Refusing provides " + prov.toString() + ": same rules as mod-id");
        }
    }

    mod->setProvides(provides);

    // Additional way of description
    if(QFileInfo(basepath.absoluteFilePath("mod-description.md")).exists())
    {
        mod->setDescription(utils::readAllTextFrom(basepath.absoluteFilePath("mod-description.md")));
    }

    // Load pipelines

    QJsonObject contents_json = json["content"].toObject();

    for(QString key : contents_json.keys())
    {
        QJsonObject content_json = contents_json[key].toObject();
        Pipeline * pipeline = nullptr;

        if(content_json["pipeline"] == "file")
        {
            pipeline = Pipeline::loadFromJson(mod, key, content_json);
        }
        else if(content_json["pipeline"] == "compile-dll")
        {
            pipeline = DllPipeline::loadFromJson(mod, key, content_json);
        }
        else if(content_json["pipeline"] == "custom")
        {
            pipeline = CustomPipeline::loadFromJson(mod, key, content_json);
        }
        else
        {
            mod->getLogger().log(Logger::Error, "modification", id, "load-pipeline", "Cannot identify pipeline " + content_json["pipeline"].toString());
        }

        if(pipeline != nullptr)
        {
            if(pipeline != nullptr)
            {
                mod->addPipeline(key, pipeline);
                mod->getLogger().log(Logger::Info, "modification", id, "load-pipeline", "Loaded pipeline " + key);
            }
            else
            {
                mod->getLogger().log(Logger::Warning, "modification", id, "load-pipeline", "Could not load pipeline " + key);
            }
        }
    }

    return mod;
}

QString Modification::name() const
{
    return m_Name;
}

void Modification::setName(const QString &Name)
{
    m_Name = Name;
}

QVersionNumber Modification::version() const
{
    return m_Version;
}

void Modification::setVersion(const QVersionNumber &Version)
{
    m_Version = Version;
}

QString Modification::description() const
{
    return m_Description;
}

void Modification::setDescription(const QString &Description)
{
    m_Description = Description;
}

void Modification::addDependency(Dependency *dep)
{
    m_Dependencies.append(dep);
}

QList<Dependency*> Modification::dependencies()
{
    return QList<Dependency*>(m_Dependencies);
}

void Modification::addPipeline(const QString &id, Pipeline *p)
{
    if(ModManager::FORBIDDEN_MOD_IDS.contains(id))
    {
        getLogger().log(Logger::Error, "modification", id, "load-pipeline", id + ": " + "Content with id 'stardewvalley', ... is forbidden.");

        throw std::invalid_argument("Illegal content ID");
    }   
    if(!utils::isValidModId(id))
    {
        getLogger().log(Logger::Error, "modification", id, "load-pipeline", id + ": " + "Content IDs be alphanumeric with additional chars '.', '-' and '_'!");

        throw std::invalid_argument("Illegal content ID");
    }   

    Pipeline * existing = getPipeline(id);

    if(existing != nullptr)
        m_Pipelines.removeAll(existing);

    m_Pipelines.append(p);
    m_PipelineIds.insert(p->id());

    // sort pipelines
    std::sort(m_Pipelines.begin(), m_Pipelines.end(), [](Pipeline * a, Pipeline * b) {
       return a->priority() < b->priority();
    });
}

int Modification::enableDefaults()
{
    int err = 0;

    for(Pipeline * pip : m_Pipelines)
    {
        if(pip->isdefault() &&(GlobalSettings::instance()->getForceUnsupported() || !pip->unsupported()))
        {
           int e = pip->setEnabled(true);

           if(e != 0)
               err = e;
        }
    }

    return err;
}

int Modification::getSupportedDefaultMods()
{
    int c = 0;

    for(Pipeline * pip : m_Pipelines)
    {
        if(pip->isdefault() &&(GlobalSettings::instance()->getForceUnsupported() || !pip->unsupported()))
        {
           ++c;
        }
    }

    return c;
}

void Modification::disableAll()
{
    for(Pipeline * pip : m_Pipelines)
    {
        pip->setEnabled(false);
    }
}

ModManager *Modification::getModManager() const
{
    return m_modManager;
}

QList<Pipeline *> Modification::getPipelines()
{
    return QList<Pipeline*>(m_Pipelines);
}

Pipeline *Modification::getPipeline(const QString &id)
{
    for(Pipeline * p : m_Pipelines)
    {
        if(p->id() == id)
            return p;
    }

    return nullptr;
}

QStringList Modification::getPipelineIds()
{
    return m_PipelineIds.toList();
}
