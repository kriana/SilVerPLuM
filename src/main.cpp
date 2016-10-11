#include "mainwindow.h"
#include "qtsingleapplication/src/QtSingleApplication"
#include "profilemanager.h"
#include "globalsettings.h"
#include <QtConcurrent>
#include "quazipcompress.h"

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
    QApplication::setApplicationVersion("1.0.1.0");

    QuazipCompress::extractDir("/home/ruman/tmp/test.zip", "/home/ruman/tmp", "1234");

    //MainWindow w;
    //w.show();
    //ret = a.exec();

    // Get rid of singletons
    delete Game::instance();
    delete ProfileManager::instance();
    delete GlobalSettings::instance();

    return ret;
}
