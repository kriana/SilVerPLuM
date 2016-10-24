#include "modrepositorysource.h"
#include "modrepository.h"

ModRepositorySource::ModRepositorySource(ModRepository *repository) : m_repository(repository)
{

}

ModRepository *ModRepositorySource::repository() const
{
    return m_repository;
}

QUrl ModRepositorySource::repositoryURL() const
{
    return m_repositoryURL;
}

void ModRepositorySource::setRepositoryURL(const QUrl &repositoryURL)
{
    m_repositoryURL = repositoryURL;
}

QString ModRepositorySource::repositoryName() const
{
    return m_repositoryName.isEmpty() ? "Unnamed repository" : m_repositoryName;
}

void ModRepositorySource::setRepositoryName(const QString &repositoryName)
{
    m_repositoryName = repositoryName;
}

QString ModRepositorySource::repositoryDescription() const
{
    return m_repositoryDescription;
}

void ModRepositorySource::setRepositoryDescription(const QString &repositoryDescription)
{
    m_repositoryDescription = repositoryDescription;
}

QString ModRepositorySource::maintainer() const
{
    return m_maintainer.isEmpty() ? "unknown" : m_maintainer;
}

void ModRepositorySource::setMaintainer(const QString &maintainer)
{
    m_maintainer = maintainer;
}

QString ModRepositorySource::website() const
{
    return m_website.isEmpty() ? "http://stardewvalley.net/" : m_website;
}

void ModRepositorySource::setWebsite(const QString &website)
{
    m_website = website;
}

ModRepositorySource *ModRepositorySource::loadFromJson(ModRepository * parent, const QJsonObject &json)
{
    ModRepositorySource * repo = new ModRepositorySource(parent);
    repo->setRepositoryName(json["name"].toString());
    repo->setRepositoryDescription(json["description"].toString());
    repo->setMaintainer(json["maintainer"].toString());
    repo->setWebsite(json["website"].toString());

    return repo;
}
