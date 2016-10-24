#ifndef MODREPOSITORYENTRY_H
#define MODREPOSITORYENTRY_H

#include <QString>
#include <QUrl>
#include <QPixmap>
#include <QJsonObject>
#include "modification.h"

class ModRepository;

class ModRepositoryEntry
{
public:
    ModRepositoryEntry(ModRepository * repo);

    ~ModRepositoryEntry();

    int id() const;

    void setId(int id);

    QUrl modConfigURL() const;

    void setModConfigURL(const QUrl &modConfigURL);

    QUrl modIconURL() const;

    void setModIconURL(const QUrl &modIconURL);

    QUrl modDescriptionURL() const;

    void setModDescriptionURL(const QUrl &modDescriptionURL);

    QUrl modDownloadURL() const;

    void setModDownloadURL(const QUrl &modDownloadURL);

    bool loadModification(const QString & mod_config, const QString & mod_description);

    Modification *modification() const;

    ModRepository *repository() const;

    QPixmap icon() const;

    void setIcon(const QPixmap &icon);

    QUrl repositorySourceURL() const;

    void setRepositorySourceURL(const QUrl &repositorySourceURL);

    /**
     * @brief Returns the modification instance that is actually installed. Otherwise nullptr.
     * @return
     */
    Modification *getInstalledMod();

    bool searchFilter(const QString & searchstring, const QString &category);

    static ModRepositoryEntry * loadConfigFromJson(ModRepository *parent, const QJsonObject & json, const QJsonObject & repojson);

private:

    ModRepository * m_repository;

    Modification * m_modification = nullptr;

    QUrl m_repositorySourceURL;

    QPixmap m_icon;

    int m_id;

    QUrl m_modConfigURL;

    QUrl m_modIconURL;

    QUrl m_modDescriptionURL;

    QUrl m_modDownloadURL;
};

#endif // MODREPOSITORYENTRY_H
