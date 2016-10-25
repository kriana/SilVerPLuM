#include "modrepositoryentry.h"
#include "modrepository.h"
#include "modmanager.h"
#include "profile.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

ModRepositoryEntry::ModRepositoryEntry(ModRepository *repo) : m_repository(repo)
{
    m_icon.load(":/resources/icons/mod-100.png");
}

ModRepositoryEntry::~ModRepositoryEntry()
{

}

int ModRepositoryEntry::id() const
{
    return m_id;
}

void ModRepositoryEntry::setId(int id)
{
    m_id = id;
}

QUrl ModRepositoryEntry::modConfigURL() const
{
    return m_modConfigURL;
}

void ModRepositoryEntry::setModConfigURL(const QUrl &modConfigURL)
{
    m_modConfigURL = modConfigURL;
}

QUrl ModRepositoryEntry::modDescriptionURL() const
{
    return m_modDescriptionURL;
}

void ModRepositoryEntry::setModDescriptionURL(const QUrl &modDescriptionURL)
{
    m_modDescriptionURL = modDescriptionURL;
}

QUrl ModRepositoryEntry::modDownloadURL() const
{
    return m_modDownloadURL;
}

void ModRepositoryEntry::setModDownloadURL(const QUrl &modDownloadURL)
{
    m_modDownloadURL = modDownloadURL;
}

bool ModRepositoryEntry::loadModification(const QString &mod_config, const QString &mod_description)
{
    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(mod_config.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError)
    {
        repository()->getLogger().log(Logger::Error, "mod-repository-entry", "load-modification", "parse-config", "Unable to parse Json: " + error.errorString());
        return false;
    }

    Modification * mod = Modification::loadFromJson(repository()->getModManager(), repository()->getModTempDir(), json.object());

    if(mod == nullptr)
    {
        repository()->getLogger().log(Logger::Error, "mod-repository-entry", "load-modification", "load-mod", "Error while loading the modification!");
        return false;
    }

    if(!mod_description.trimmed().isEmpty())
    {
        mod->setDescription(mod_description);
    }

    m_modification = mod;

    return true;
}

Modification *ModRepositoryEntry::modification() const
{
    return m_modification;
}

ModRepository *ModRepositoryEntry::repository() const
{
    return m_repository;
}

QPixmap ModRepositoryEntry::icon() const
{
    return m_icon;
}

void ModRepositoryEntry::setIcon(const QPixmap &icon)
{
    if(!icon.isNull())
        m_icon = icon;
}

Modification * ModRepositoryEntry::getInstalledMod()
{
    if(m_modification != nullptr)
    {
        for(Modification * mod : repository()->getModManager()->getModifications())
        {
            if(mod->id() == m_modification->id())
                return mod;
        }
    }

    return nullptr;
}

bool ModRepositoryEntry::searchFilter(const QString &searchstring, const QString & category)
{
    if(!searchstring.isEmpty())
    {
        bool search = false;

        search |= (m_modDownloadURL.toDisplayString().toLower().contains(searchstring));
        search |= (m_repositorySource->repositoryName().toLower().contains(searchstring));
        search |= (m_repositorySource->repositoryDescription().toLower().contains(searchstring));
        search |= modification()->search(searchstring);

        if(!search)
            return false;
    }

    if(!category.isEmpty())
        return modification()->isInCategory(category);

    return true;
}

ModRepositoryEntry *ModRepositoryEntry::loadConfigFromJson(ModRepository * parent, const QJsonObject &json, const QJsonObject &repojson)
{
    QString prefix = json["url-prefix"].toString();
    QUrl modConfigURL = json["config"].toString().isEmpty() ? QUrl() : QUrl::fromEncoded(insertPrefix(json["config"].toString(), prefix).toLocal8Bit());
    QUrl modDescriptionURL = json["description"].toString().isEmpty() ? QUrl() : QUrl::fromEncoded(insertPrefix(json["description"].toString(), prefix).toLocal8Bit());
    QUrl modIconURL = json["icon"].toString().isEmpty() ? QUrl() : QUrl::fromEncoded(insertPrefix(json["icon"].toString(), prefix).toLocal8Bit());
    QUrl modDownloadURL = json["download"].toString().isEmpty() ? QUrl() : QUrl::fromEncoded(insertPrefix(json["download"].toString(), prefix).toLocal8Bit());

    if(!modConfigURL.isValid() || !modDownloadURL.isValid())
    {
        return nullptr;
    }

    ModRepositoryEntry * result = new ModRepositoryEntry(parent);
    result->setModConfigURL(modConfigURL);
    result->setModDescriptionURL(modDescriptionURL);
    result->setModIconURL(modIconURL);
    result->setModDownloadURL(modDownloadURL);

    return result;
}

ModRepositorySource *ModRepositoryEntry::getRepositorySource() const
{
    return m_repositorySource;
}

void ModRepositoryEntry::setRepositorySource(ModRepositorySource *repositorySource)
{
    m_repositorySource = repositorySource;
}

QString ModRepositoryEntry::insertPrefix(const QString &url, const QString &prefix)
{
    if(url.contains("://"))
        return url;
    return prefix + url;
}

QUrl ModRepositoryEntry::modIconURL() const
{
    return m_modIconURL;
}

void ModRepositoryEntry::setModIconURL(const QUrl &modIconURL)
{
    m_modIconURL = modIconURL;
}
