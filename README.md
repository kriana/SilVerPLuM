# SilVerPLuM
**S**tardew **V**alley **P**rofiles, **L**auncher and **M**od-manager

is a cross-platform tool to manage different Stardew Valley profiles with their own mods and savegames. It is written in C++/Qt and brings following features:

## Profile manager
You can have different profiles with their own savegames, mods and even Stardew Valley installations. For example you can keep old versions of Stardew Valley in a separate place to be still able to keep playing when an update is released.

## Savegame manager
Included is a simple savegame manager that can make backups of your savegames with a couple of clicks.

## Mod manager
The mod manager supports content replacer mods and DLL mods. It has dependency-checking, so you don't have to fear that you are missing a mod that is needed by another mod. A simple interface offers easy enabling/disabling of mods and optional content of mods with just one click.

# For mod developers

The mod manager of SilVerPLuM is built with flexibility in mind and offers classic file-replacer mods, an interface for custom game launchers and an on-the-fly compilation feature. Mods are split in submods that are marked as 'default' or unsupported on a specific platform.

## Mods

Mods are organized in folders that can be compressed into *.zip files to make them portable. Here's a typical directory content:

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

* `requires` is a list of mods that your mod will need to be able to run. The mod manager is priority-aware by default and will also look for a correct order. If you would require other mods, it may look like this: `"requires" : [ "stardewvalley==1.1", "mod1>1.0", "apimod2<=2.0.3" ]`
* `content` contains the actual content (submods). Detailed explanations will follow.
