#Storm Modding API

Currently in ALPHA | Not compatible with SMAPI (or its mods) | [GitLab Source Code](https://gitlab.com/Demmonic/Storm/) | [#stardewvalley-mods](http://irc//freenode.net/stardewvalley-mods) on freenode for development discussion

This is super alpha right now, things will break time and time again until we set a milestone. You can download it below however.
We currently need help knowing what classes and events mod makers want exposed right now in order to make the best mods possible.

Features:

* Dynamically modifies the game's executable at runtime to expose private data and provide callbacks.
* Provides a layer of abstraction for a stable, maintainable modding environment.
* We use Mono.Cecil for our MSIL injection, DynamicProxy for creating instances of any games classes, and Json.NET for serialization.
* Because of the way Storm is built, game updates shouldn't break mods and at most would require an update to Storm only.
 
