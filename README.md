![Logo](https://rumangerst.github.io/SilVerPLuM/docs/images/logo.png)

# SilVerPLuM
**S** tardew **V** alley **P** rofiles, **L** auncher and **M** od-manager

is a cross-platform tool to manage different Stardew Valley profiles with their own mods and savegames. It is written in C++/Qt and brings following features:

## Profile manager
You can have different profiles with their own savegames, mods and even Stardew Valley installations. For example you can keep old versions of Stardew Valley in a separate place to be still able to keep playing when an update is released.

## Savegame manager
Included is a simple savegame manager that can make backups of your savegames with a couple of clicks.

## Mod manager
The mod manager supports content replacer mods and DLL mods. It has dependency-checking, so you don't have to fear that you are missing a mod that is needed by another mod. A simple interface offers easy enabling/disabling of mods and optional content of mods with just one click.

![Play tab](https://rumangerst.github.io/SilVerPLuM/docs/images/tab_play.png)

## All features

* Profile manager for separated savegames, mods and game installations
* Export/import profiles
* Savegame backups
* Remove redundant backups
* Optional auto-backup before launch and every x minutes
* Copy savegames and backups across profiles
* Make a backup to its own savegame
* Export/import savegames
* Support for content-replacer mods
* Modders can define their own launchers for DLL mods and other tools
* Dependency checking for mods
* Optional mod content
* Compilation pipeline for cross-platform DLL mods
* Copy mods across profiles
* ...

# Installation

You can find precompiled packages here: [Download](https://github.com/rumangerst/SilVerPLuM/releases)

Just download the package and extract it somewhere. Run SilVerPLuM.exe or SiLVerPLuM.

## System requirements

### Windows

* [Microsoft Build Tools 2015](https://www.microsoft.com/de-DE/download/details.aspx?id=48159) for compiling DLL-mods
* [Nuget CLI](https://dist.nuget.org/win-x86-commandline/latest/nuget.exe) for compiling DLL-mods
* [Python 3.5 or higher](https://www.python.org/downloads/windows/) for mods with custom scripts. Go to 'Latest Python 3 Release', scroll down and choose 'Windows x86-64 executable installer' or 'Windows x86 executable installer'

You may need to set the correct paths of some external programs in SilVerPLuM's application settings.

### Linux

* Qt5 5.7 or higher (Arch: `qt5-base`, Debian: `qt5-default`)
* Quazip5 (Arch: `quazip`, Debian: `libquazip5-1`)
* Nuget CLI (Arch: `nuget`, Debian: `nuget` or download the Windows version)
* Python3 (Arch: `python`, Debian: `python3`)
* Mono (Arch: `mono`, Debian: `mono`)

You may need to set the correct paths of some external programs in SilVerPLuM's application settings.

## Building
SilVerPLuM is written in Qt5 with qmake building system and has following dependencies:

* Qt5 (core gui network concurrent xml)
* quazip5 / quazip
* zlib

If you want to use the commandline, you can use `qmake` and then `make`. Otherwise you can use an IDE like QtCreator. On Mac and Windows check if there's an additional build step `rcc -binary icontheme.qrc icontheme.rcc` to include icon resources. The resulting icontheme.rcc should be present in the binary folder.

## Reporting issues
If you have an issue, take a look at the corresponding [Wiki entry](https://github.com/rumangerst/SilVerPLuM/wiki/Finding-problems) for steps how to single out the problem and the correct way to report them.

# Using SilVerPLuM

## Concepts
You might find it helpful to first see some quick explanations about the terms associated with SilVerPLuM.

### Profile
A profile is a separate container for your savegames, backups and mods. If you start a game with SilVerPLuM, the profile will be loaded into the game. After running the game, the profile will be unloaded and savegames will be copied back into your profile.
A profile also is able to have it's own Stardew Valley installation and savegame folder (If somebody manages to change it).

### Launcher
A launcher launches an executable in your game folder. By default, there's always the 'Vanilla Launcher' that just starts Stardew Valley.
Modders can define their own launchers that for example load modifications.

## User interface
If you start SilVerPLuM, you will see a launcher screen to start Stardew Valley right away **if** it's in the standard directory. Otherwise you'll need to go to the configuration tab and select the correct Stardew Valley directory.

## 'Play' tab

* 'Play' starts the current launcher (by default just Stardew Valley). Click on the arrow to list other launchers
* 'Application Settings' will let you tweak global settings of SilVerPLuM
* 'Profile log' opens the log of the current profile. It contains information how things are loaded, if errors happened and more.

![Play tab](https://rumangerst.github.io/SilVerPLuM/docs/images/tab_play.png)

## 'Configure' tab
This tab contains the profile settings such as the Stardew Valley directory, which launcher should be the default and more.
This tab has a profile manager that allows you to create, duplicate and remove profiles.

![Play tab](https://rumangerst.github.io/SilVerPLuM/docs/images/tab_configure.png)

## 'Modify' tab

This tab contains the mod manager. You can install mods by clicking the respective button on the top. Each mod is shown as its own entry in the list. With 'Show more' you can show more information, hand-pick optional submods and delete a mod.

If you install more complex mods, you may get a dependency warning that tells you which mod is missing. Also keep in mind that dependencies must be *above* the requesting mod as SilVerPLuM goes from top to bottom and one by one installs the mods.

This tab has a profile manager that allows you to create, duplicate and remove profiles.

You can see that there are buttons to priotize the mods (move them up or down). If mods don't interfere or depend on each other, the order doesn't matter. But if you e.g. install a mod modifying some other mod, the mod with the "newer" files must be placed at bottom. It's like this because mods at the top are installed *first* and other mods can then overwrite those files.

![Play tab](https://rumangerst.github.io/SilVerPLuM/docs/images/tab_modify.png)

## 'Manage' tab

This tab contains the savegame manager. It will list your current savegames and allows you to create a backup with just one click.

If you click on the arrow next to a savegame or a backup, you can do some additional actions:

* Delete the backup / the savegame - If you delete a savegame and the backup is still there, you can still restore them
* Copy to another profile - Creates a copy of your savegame and backups in another profile. It will allow you to overwrite an existing savegame or just rename the copy
* Single out - Create a new savegame out of a backup or another savegame

This tab has a profile manager that allows you to create, duplicate and remove profiles.

![Play tab](https://rumangerst.github.io/SilVerPLuM/docs/images/tab_manage.png)

## Tips

### Temporarily 'disable' a savegame
1. Create a backup
2. Delete only the current savegame (in the arrow menu)

### See what's done by SilVerPLuM
1. Click on the arrow next to 'Play'
2. Select "Debug launcher"
3. Visit your game director, etc. and look if everything is correct

### Make a mod package
1. Click on the 'Export profile to file' button next to the duplicate button
2. Save your profile as \*.zip
3. Share it online

# Q.T.M.O - Questions that might occur

## My savegame is broken!
There's unfortunately no guarantee that everything works. There can be always bugs and some error maybe caused by some other program can lead to this. Always make backups.

## My game won't load
Should only happen if something crashed. Just verify your installation with Steam or re-install your game. You can also report this incident (plus the contents of 'Profile log') - maybe it's caused by a bug.

## My mod won't load
You can see the error in 'Profile log'. If it's not caused by you, report this incident.

## Why not FAQ?
No questions have been asked so far. They aren't 'frequently asked questions' (;

## Wait ... where does the i, l, e, r, and u in SilVerPLuM came from?
Actually the program's name should be SVPLM. I rotated the remaining letters until something usable came out. Even more loose variant of [making acronyms](http://www.phdcomics.com/comics.php?f=1100).

## This program doesn't want to load my mods
SilVerPLuM needs a certain structure of mod files. Modders unfortunately have to make mods specific for SilVerPLuM.

## Why can't I download mods
There *may* be a feature that can download mods, but this must be handled with care or it will go wrong. Already experienced it.

## Why only \*.zip files?
Because they are widely known and work everywhere. Also there's a nice library that handles this and integrates well.

# Create mods for SilVerPLuM

SilVerPLuM has its own mod format. You can find some more information in the [wiki](https://github.com/rumangerst/SilVerPLuM/wiki/Create-Mods).
