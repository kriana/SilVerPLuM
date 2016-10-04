#include "modification.h"
#include "modmanager.h"
#include "profile.h"
#include <QDebug>
#include "filepipeline.h"


QString Modification::getAuthor() const
{
    return m_Author;
}

void Modification::setAuthor(const QString &Author)
{
    m_Author = Author;
}

QString Modification::getUrl() const
{
    return m_Url;
}

void Modification::setUrl(const QString &Url)
{
    m_Url = Url;
}

QString Modification::getLicense() const
{
    return m_License;
}

void Modification::setLicense(const QString &License)
{
    m_License = License;
}

Modification::Modification(ModManager *modmgr, const QString &id) : m_modManager(modmgr), m_Id(id)
{

}

Modification::~Modification()
{
    for(Dependency * dep : m_Dependencies)
    {
        delete dep;
    }

    for(Pipeline * p : m_Content)
    {
        delete p;
    }
}

Modification * Modification::loadFromJson(ModManager * modmgr, const QJsonObject &json)
{
    QString id = json["id"].toString();

    if(id.isEmpty())
        throw std::invalid_argument("Modification ID is empty!");

    Modification * mod = new Modification(modmgr, id);

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

    // Load pipelines

    QJsonObject contents_json = json["content"].toObject();

    for(QString key : contents_json.keys())
    {
        QJsonObject content_json = contents_json[key].toObject();

        if(content_json["pipeline"] == "file")
        {
            FilePipeline * pipeline = nullptr;

            try
            {
                pipeline = FilePipeline::loadFromJson(mod, key, content_json);
            }
            catch(...)
            {

            }

            if(pipeline != nullptr)
            {
                mod->addContent(key, pipeline);
                qInfo() << "- Content " << key << " is available";
            }
            else
            {
                qWarning() << "- Content " << key << " COULD NOT BE LOADED!";
            }
        }
        else
        {
            qWarning() << "Cannot identify pipeline " << content_json["pipeline"];
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

void Modification::addContent(const QString &id, Pipeline *p)
{
    m_Content[id] = p;
}

Pipeline *Modification::getContent(const QString &id)
{
    return m_Content[id];
}

QDir Modification::modBasePath()
{
    return m_modManager->profile()->profileModDir().absoluteFilePath(m_Id);
}

void Modification::enableDefaults()
{
    for(Pipeline * pip : m_Content.values())
    {
        if(pip->isdefault())
        {
            m_modManager->setEnabled(m_Id, pip->id(), true);
        }
    }
}

ModManager *Modification::getModManager() const
{
    return m_modManager;
}

Pipeline *Modification::getPipeline(const QString &id)
{
    return m_Content[id];
}

QStringList Modification::getPipelineIds()
{
    return m_Content.keys();
}
