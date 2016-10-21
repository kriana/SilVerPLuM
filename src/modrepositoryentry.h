#ifndef MODREPOSITORYENTRY_H
#define MODREPOSITORYENTRY_H

#include <QString>
#include <QUrl>
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

    void loadModification(const QString & mod_config, const QString & mod_description);

    Modification *modification() const;

    ModRepository *repository() const;

private:

    ModRepository * m_repository;

    Modification * m_modification = nullptr;

    int m_id;

    QUrl m_modConfigURL;

    QUrl m_modIconURL;

    QUrl m_modDescriptionURL;

    QUrl m_modDownloadURL;
};

#endif // MODREPOSITORYENTRY_H
