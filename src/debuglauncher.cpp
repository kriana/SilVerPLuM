#include "debuglauncher.h"
#include <QMessageBox>
#include "logviewer.h"
#include "profile.h"
#include "platform.h"
#include "game.h"
#include <QDesktopServices>
#include <QUrl>

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
        dlg.setInformativeText("The profile should now be active. Select one of the options:");
        dlg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Open | QMessageBox::Save | QMessageBox::Yes | QMessageBox::Close);
        dlg.setButtonText(QMessageBox::Yes, "Show profile log");
        dlg.setButtonText(QMessageBox::Close, "Finish and close log");
        dlg.setButtonText(QMessageBox::Cancel, "Finish and keep log open");
        dlg.setButtonText(QMessageBox::Open, "Open game dir.");
        dlg.setButtonText(QMessageBox::Save, "Open savegame dir.");

        switch(dlg.exec())
        {
        case QMessageBox::Yes:
            LogViewer::execForProfile(this->getProfile());
            break;
        case QMessageBox::Open:
            QDesktopServices::openUrl(QUrl::fromLocalFile(getProfile()->StardewValleyDir().absolutePath()));
            break;
        case QMessageBox::Save:
            QDesktopServices::openUrl(QUrl::fromLocalFile(getProfile()->StardewValleySavegameDir().absolutePath()));
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
