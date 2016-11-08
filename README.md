**Development of this software ended.**

|[Download](https://github.com/rumangerst/SilVerPLuM#installation)|[Wiki](https://github.com/rumangerst/SilVerPLuM/wiki)|[Tutorial: Steam overlay & achievements](https://github.com/rumangerst/SilVerPLuM/wiki/Tutorial:-Steam-overlay-and-achievements)|[Tutorial: Import mods](https://github.com/rumangerst/SilVerPLuM/wiki/Modding-tutorial:-Use-the-mod-importer)|[Tutorial: Create mods](https://github.com/rumangerst/SilVerPLuM/wiki/Modding-tutorial:-Create-a-mod)|
|----|----|----|----|----|

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

**Runtime dependencies**

* Qt5 5.7 or higher (Arch: `qt5-base`, Debian: `qt5-default`)
* Quazip5 (Arch: `quazip`, Debian: `libquazip5-1`)

The updated Linux packages now provide the needed libraries if your distribution doesn't offer the needed ones. Just start `SilVerPLuM.sh` instead of `SilVerPLuM` to use them. Other users can delete the lib and plugin folder safely.

You may need to set the correct paths of some external programs in SilVerPLuM's application settings.

## Building
SilVerPLuM is written in Qt5 with qmake building system and has following dependencies:

* Qt5 (core gui network concurrent xml)
* quazip5 / quazip
* zlib

If you want to use the commandline, you can use `qmake` and then `make`. Otherwise you can use an IDE like QtCreator. On Mac and Windows check if there's an additional build step `rcc -binary icontheme.qrc icontheme.rcc` to include icon resources. The resulting icontheme.rcc should be present in the binary folder.

## Reporting issues
If you have an issue, take a look at the corresponding [Wiki entry](https://github.com/rumangerst/SilVerPLuM/wiki/Finding-problems) for steps how to single out the problem and the correct way to report them.

