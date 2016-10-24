#ifndef MODREPOSITORYSOURCE_H
#define MODREPOSITORYSOURCE_H

#include <QUrl>
#include <QJsonObject>
#include <QString>

class ModRepository;

class ModRepositorySource
{
public:
    ModRepositorySource(ModRepository * repository);

    ModRepository *repository() const;

    QUrl repositoryURL() const;

    void setRepositoryURL(const QUrl &repositoryURL);

    QString repositoryName() const;

    void setRepositoryName(const QString &repositoryName);

    QString repositoryDescription() const;

    void setRepositoryDescription(const QString &repositoryDescription);

    QString maintainer() const;

    void setMaintainer(const QString &maintainer);

    QString website() const;

    void setWebsite(const QString &website);

    static ModRepositorySource * loadFromJson(ModRepository *parent, const QJsonObject & json);

private:

    ModRepository * m_repository;

    QUrl m_repositoryURL;

    QString m_repositoryName;

    QString m_repositoryDescription;

    QString m_maintainer;

    QString m_website;
};

#endif // MODREPOSITORYSOURCE_H
