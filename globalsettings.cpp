#include "globalsettings.h"

GlobalSettings * GlobalSettings::m_pInstance = nullptr;

GlobalSettings::GlobalSettings()
{
    m_Settings = new QSettings("CSDVMM", "CSDVMM");
}

GlobalSettings::~GlobalSettings()
{
    delete m_Settings;
}

GlobalSettings *GlobalSettings::instance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new GlobalSettings();
    }

    return m_pInstance;
}

void GlobalSettings::setWindowState(QMainWindow *widget)
{
    m_Settings->setValue("Window/Geometry", widget->saveGeometry());
    m_Settings->setValue("Window/State", widget->saveState());
}

void GlobalSettings::getWindowState(QMainWindow *widget)
{
    widget->restoreGeometry(m_Settings->value("Window/Geometry").toByteArray());
    widget->restoreState(m_Settings->value("Window/State").toByteArray());
}
