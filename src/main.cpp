#include "mainwindow.h"
#include "qtsingleapplication/src/QtSingleApplication"
#include "profilemanager.h"
#include "globalsettings.h"
#include <QtConcurrent>

int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);

    if(a.isRunning())
    {
        a.activateWindow();
        return 0;
    }

    int ret = -1;

    // Import the icon theme if its not set. Needed for Windows and MacOS
    if(QIcon::themeName().isEmpty())
    {
        QIcon::setThemeName("breeze");
    }

    QApplication::setApplicationName("SilVerPLuM");
    QApplication::setApplicationVersion("1.0.0.1");

    MainWindow w;
    w.show();
    ret = a.exec();

    // Get rid of singletons
    delete Game::instance();
    delete ProfileManager::instance();
    delete GlobalSettings::instance();

    return ret;
}
