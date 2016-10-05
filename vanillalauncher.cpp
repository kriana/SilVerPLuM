#include "vanillalauncher.h"
#include "profile.h"
#include "platform.h"
#include "game.h"

QString VanillaLauncher::ID = "vanilla";

VanillaLauncher::VanillaLauncher(Profile * p) : Launcher(p)
{
    setId("vanilla");
    setName("Stardew Valley");
    setDescription("Launches the vanilla game. Only allows content replacer mods (XNB).");
    setExecutable(Platform::Windows, LauncherExecutable("StardewValley.exe"));
    setExecutable(Platform::Linux, LauncherExecutable("StardewValley"));
    setExecutable(Platform::Mac, LauncherExecutable("StardewValley"));
}

