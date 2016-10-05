#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QSettings>
#include <QWidget>
#include <QMainWindow>


class GlobalSettings
{
public:

    ~GlobalSettings();

    static GlobalSettings * instance();

    void setWindowState(QMainWindow * widget);

    void getWindowState(QMainWindow *widget);

    bool getDLLRedirectXNA();

    void setDLLRedirectXNA(bool enabled);

    bool getForceUnsupported();

    void setForceUnsupported(bool enabled);

    bool getRunningBackupSDVSavegames();

    void setRunningBackupSDVSavegames(bool enabled);

    bool getRunningBackupProfileSavegames();

    void setRunningBackupProfileSavegames(bool enabled);

    QString getProgramMSBUILD();

    void setProgramMSBUILD(const QString & program);

    QString getProgramNuget();

    void setProgramNuget(const QString & program);

private:

    static GlobalSettings * m_pInstance;

    GlobalSettings();

    QSettings * m_Settings;
};

#endif // GLOBALSETTINGS_H
