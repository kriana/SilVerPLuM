#ifndef MODREPOSITORYENTRY_H
#define MODREPOSITORYENTRY_H

#include <QString>
#include <QUrl>

class ModRepositoryEntry
{
public:
    ModRepositoryEntry();

    int id() const;

    void setId(int id);

    QUrl modConfigURL() const;

    void setModConfigURL(const QUrl &modConfigURL);

    QUrl modDescriptionURL() const;

    void setModDescriptionURL(const QUrl &modDescriptionURL);

    QUrl modDownloadURL() const;

    void setModDownloadURL(const QUrl &modDownloadURL);

private:

    int m_id;

    QUrl m_modConfigURL;

    QUrl m_modDescriptionURL;

    QUrl m_modDownloadURL;
};

#endif // MODREPOSITORYENTRY_H
