# SilVerPLuM
**S** tardew **V** alley **P** rofiles, **L** auncher and **M** od-manager

is a cross-platform tool to manage different Stardew Valley profiles with their own mods and savegames. It is written in C++/Qt and brings following features:

## Profile manager
You can have different profiles with their own savegames, mods and even Stardew Valley installations. For example you can keep old versions of Stardew Valley in a separate place to be still able to keep playing when an update is released.

## Savegame manager
Included is a simple savegame manager that can make backups of your savegames with a couple of clicks.

## Mod manager
The mod manager supports content replacer mods and DLL mods. It has dependency-checking, so you don't have to fear that you are missing a mod that is needed by another mod. A simple interface offers easy enabling/disabling of mods and optional content of mods with just one click.

# Installation

<Precompiled>

SilVerPLuM will need following programs to be able to compile DLL mods:

* Nuget
* msbuild (Windows) or xbuild (Mac, Linux)

You may need to set the correct paths of these programs in SilVerPLuM's application settings.

## Building
SilVerPLuM is written in Qt5 with qmake building system and has following dependencies:

* Qt5 (core gui concurrent xml)
* Quazip5
* zlib

If you want to use the commandline, you can use `qmake` and then `make`. Otherwise you can use an IDE like QtCreator.

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

## 'Configure' tab
This tab contains the profile settings such as the Stardew Valley directory, which launcher should be the default and more.
This tab has a profile manager that allows you to create, duplicate and remove profiles.

## 'Modify' tab

This tab contains the mod manager. You can install mods by clicking the respective button on the top. Each mod is shown as its own entry in the list. With 'Show more' you can show more information, hand-pick optional submods and delete a mod.

If you install more complex mods, you may get a dependency warning that tells you which mod is missing. Alos keep in mind that dependencies must be *above* the requesting mod as SilVerPLuM goes from top to bottom and one by one installs the mods.

This tab has a profile manager that allows you to create, duplicate and remove profiles.

## 'Manage' tab

This tab contains the savegame manager. It will list your current savegames and allows you to create a backup with just one click.

If you click on the arrow next to a savegame or a backup, you can do some additional actions:

* Delete the backup / the savegame - If you delete a savegame and the backup is still there, you can still restore them
* Copy to another profile - Creates a copy of your savegame and backups in another profile. It will allow you to overwrite an existing savegame or just rename the copy
* Single out - Create a new savegame out of a backup or another savegame

This tab has a profile manager that allows you to create, duplicate and remove profiles.

# For mod developers

The mod manager of SilVerPLuM is built with flexibility in mind and offers classic file-replacer mods, an interface for custom game launchers and an on-the-fly compilation feature. Mods are split in submods that are marked as 'default' or unsupported on a specific platform.

## Mods

Mods are organized in folders that can be compressed into \*.zip files to make them portable. Here's a typical directory content:

```
./mod.json
./core/
./alternative-sebastian/
```

* `mod.json` is the main configuration file. It is mandatory.
* `core` and `alternative-sebastian` are both submod content folders. Their name is defined in mod.json and SilVerPLuM will look for the respective files in those folders.

Let's assume here that the content folders contain portraits:

```
./core/Content/Portraits/Emily.xnb
./core/Content/Portraits/Linus.xnb
./core/Content/Portraits/Sebastian.xnb
./alternative-sebastian/Content/Portraits/Sebastian.xnb
```

Now let's have a look into the mod.json file:

```json
{
  "id" : "portrait-mod",
  "name" : "Portrait mod",
  "author" : "creativeguy",
  "license" : "CC0",
  "url" : "http://community.playstarbound.com/",
  "version" : "1.0.0",
  "requires" : [ "stardewvalley==1.1" ],
  "content" : {
    "core" : {
      "name" : "The core mod",
      "description" : "",
      "default" : true,
      "priority" : 0,
      "pipeline" : "file",
      "location" : "file",
      "platforms" : ["windows", "linux", "mac"],
      "installables" : {
        "Content" : "Content"
      },
      "launchers" : {}
	  },
    "alternative-sebastian" : {
      "name" : "An alternative Sebastian",
      "description" : "With some cool glasses!",
      "default" : true,
      "priority" : 1,
      "pipeline" : "file",
      "location" : "file",
      "platforms" : ["windows", "linux", "mac"],
      "installables" : {
        "Content" : "Content"
      },
      "launchers" : {}
	  }
    }    
  }
}

```

The top-most entries should not need an explanation. Just some information for the user. Now to the technical parts:

* `id` must be lowercase and consist only of numbers and letters with '\_', '.' and '-' allowed
* `requires` is a list of mods that your mod will need to be able to run. The mod manager is priority-aware by default and will also look for a correct order. If you would require other mods, it may look like this: `"requires" : [ "stardewvalley==1.1", "mod1>1.0", "apimod2<=2.0.3" ]`
* `content` contains the actual content (submods). Detailed explanations below.

## Content

A mod is subdivided into several (or just one) submods that act both as options to give a user additional choice and separating DLL/EXE mods from content replacer or file-mods. Let's have an explanation for each setting in a content entry:

* the key/id must be lowercase and consist only of numbers and letters with '\_', '.' and '-' allowed. The content folder in the filesystem **must** have the same name
* `name` - Obvious
* `description` - Obvious (supports markdown)
* `priority` - Smaller numer = Installed first -> May be overridden.
* `pipeline` - The pipeline used that defines which additional behaviors shall be triggered on activation. More info below.
* `location` - For future version
* `platforms` - If the user's platform is not in this list, the mod cannot not be activated (Unless this check is turned off in the application settings)
* `installables` - key = File or folder relative to the submod dir, value = File or folder relative to Stardew Valley dir. Note that this does not work like 'Copy file from here to this folder', but more like 'This file should have the name xyz in Stardew Valley folder'
* `launchers` - Here you can define custom launchers. More info below.

## Pipelines

A pipeline is defined by some additional operations that are done at mod activation (internally called 'priming'). This activation process may e.g. create files that are not in the package.

There are currently two pipelines: `file` and `compile-dll`

### File pipeline (file)
Does nothing on activation. Use this if all your files are already present.

### Compiler pipeline (dll-compile)
This pipeline compiles the .NET solution that is present in the content directory by calling MSBUILD/xbuild. Just put your solution into the content directory like this:

```
/mod.json
/super-dll-mod/MyMod.sln
/super-dll-mod/MyMod/MyMod.csproj
...
```

This pipeline has additional options in the mod configuration.

* `nuget-restore` - Run `nuget restore` as part of compilation process
* `references` - Maps .NET references to DLLs. More info below.

Here's an example:

```
{
  "id" : "testlauncher",
  "name" : "Test Launcher",
  "author" : "mrboese",
  "license" : "GPLv3",
  "url" : "https://github.com/rumangerst/",
  "version" : "1.0.0",
  "requires" : [ "stardewvalley==1.1" ],
  "content" : {
    "testlauncher" : {
      "name" : "The Launcher",
      "description" : "Contains the DLL and a launcher. Don't forget to activate it!",
      "default" : true,
      "platforms" : ["windows", "linux", "mac"],
      "priority" : 0,
      "pipeline" : "compile-dll",
      "nuget-restore" : true,
      "references" : { },
      "location" : "file",
      "installables" : {
		  "TestLauncher/bin/Debug/TestLauncher.exe" : "TestLauncher.exe",
		  "TestLauncher/bin/Debug/TestLauncher" : "TestLauncher"
		  },
      "launchers" : {}
	  }
    }
  }
}
```

#### Reference mapping

How to compile against a modding API or another DLL in some mod or just Stardew Valley? The `reference` setting will solve this problems automatically. It looks for the specified .NET reference and hints the correct DLL that can be in any mod or Stardew Valley.

Entries need to have following syntax: `"<reference>" : "<modid>://<relative-path>"`. Stardew Valley will be mapped to id 'stardewvalley'.

Following references are included by SilVerPLuM and don't need to be added manually:

* StardewValley.exe
* xTile.dll
* XNA/MonoGame (The integrated resolver will interchange them automatically)

Here's an example for a DLL provided by some API mod:

```
"references" : {
  "StardewSuperAPI" : "stardewsuperapi://api/StardewSuperAPI/bin/Debug/StardewSuperAPI.dll"
}
```

## Define launchers

Launchers will run executables with a defined set of arguments. The user can select them from the GUI.

It has following settings:

* key/id - Same rules as with all other ids. Must be unique to the whole profile.
* Obvious name and description
* `executables` - This will define the executables for a platform. You may leave platforms out if you don't support them.

Let's have an example:

```
{
  "id" : "testlauncher",
  "name" : "Test Launcher",
  "author" : "mrboese",
  "license" : "GPLv3",
  "url" : "https://github.com/rumangerst/",
  "version" : "1.0.0",
  "requires" : [ "stardewvalley==1.1" ],
  "content" : {
    "testlauncher" : {
      "name" : "The Launcher",
      "description" : "Contains the DLL and a launcher. Don't forget to activate it!",
      "default" : true,
      "platforms" : ["windows", "linux", "mac"],
      "priority" : 0,
      "pipeline" : "compile-dll",
      "nuget-restore" : true,
      "references" : { },
      "location" : "file",
      "installables" : {
		  "TestLauncher/bin/Debug/TestLauncher.exe" : "TestLauncher.exe",
		  "TestLauncher/bin/Debug/TestLauncher" : "TestLauncher"
		  },
      "launchers" : {
		  "test-launcher" : {
			  "name" : "Test",			  
			  "description" : "Runs konsole",
			  "executables" : {
				  "linux" : { "executable" : "stardewvalley://TestLauncher", "arguments" : [], "workdir" : "stardewvalley://" },
          "mac" : { "executable" : "stardewvalley://TestLauncher", "arguments" : [], "workdir" : "stardewvalley://" },
          "windows" : { "executable" : "stardewvalley://TestLauncher.exe", "arguments" : [], "workdir" : "stardewvalley://" }
			  }
		  }
	  }
    }
  }
}

```

### Executables

An executable points to some file in a mod or Stardew Valley. You can define arguments and set the workdir. Both executable and workdir have the same 'mod-url' syntax as with references.

Note here that for Linux and Mac you'll need a script that runs `mono TestLauncher.exe` to start the executable. On Windows the exe can be run directly. SilVerPLuM will change file-permissions, so the executables are able to run.
