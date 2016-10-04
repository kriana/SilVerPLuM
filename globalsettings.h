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

private:

    static GlobalSettings * m_pInstance;

    GlobalSettings();

    QSettings * m_Settings;
};

#endif // GLOBALSETTINGS_H
