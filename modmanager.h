#ifndef MODMANAGER_H
#define MODMANAGER_H

#include <QDir>
#include <QString>
#include <QMap>
#include <QSettings>
#include "modification.h"

class Profile;

class ModManager
{
public:
    ModManager(Profile * profile);

    ~ModManager();

    Profile *profile() const;

    void initialize();

    Modification * getModification(const QString & mod);

    Pipeline * getPipeline(const QString & mod, const QString & content);

    void setEnabled(const QString & mod, const QString & content, bool enabled);

    bool isEnabled(const QString & mod, const QString & content);

private:

    QSettings * m_config;

    Profile * m_profile;

    QMap<QString, Modification *> m_mods;

    void loadMod(const QDir & directory);

    void loadMods();
};

#endif // MODMANAGER_H
