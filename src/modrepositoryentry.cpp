#include "modrepositoryentry.h"

ModRepositoryEntry::ModRepositoryEntry(ModRepository *repo) : m_repository(repo)
{

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

void ModRepositoryEntry::loadModification(const QString &mod_config, const QString &mod_description)
{

}

Modification *ModRepositoryEntry::modification() const
{
    return m_modification;
}

ModRepository *ModRepositoryEntry::repository() const
{
    return m_repository;
}
