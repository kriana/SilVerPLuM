#include "debuglauncher.h"
#include <QMessageBox>
#include "logviewer.h"
#include "profile.h"
#include "platform.h"
#include "game.h"

QString DebugLauncher::ID = "debug";

DebugLauncher::DebugLauncher(Profile * p) : Launcher(p)
{
    setId("debug");
    setName("Debug Launcher");
    setDescription("For testing modifications. Launches nothing, but prevents uninstallation until manually closed.");
    setExecutable(Platform::Windows, LauncherExecutable("stardewvalley://StardewValley.exe"));
    setExecutable(Platform::Linux, LauncherExecutable("stardewvalley://StardewValley"));
    setExecutable(Platform::Mac, LauncherExecutable("stardewvalley://StardewValley"));
}

void DebugLauncher::start()
{
    while(true)
    {
        QMessageBox dlg;

        dlg.setText("Debug Launcher");
        dlg.setInformativeText("The profile should new be active. Select one of the options:");
        dlg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes | QMessageBox::Close);
        dlg.setButtonText(QMessageBox::Yes, "Show profile log");
        dlg.setButtonText(QMessageBox::Close, "Finish and close log");
        dlg.setButtonText(QMessageBox::Cancel, "Finish and keep log open");

        switch(dlg.exec())
        {
        case QMessageBox::Yes:
            LogViewer::execForProfile(this->getProfile());
            break;
        case QMessageBox::Cancel:
            emit finished(-1);
            return;
        case QMessageBox::Close:
            emit finished(0);
            return;
        }
    }
}
