/*
    Copyright 2016 Cody R. (Demmonic), Matt Stevens (Handsome Matt)

    Storm is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Storm is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Storm.  If not, see <http://www.gnu.org/licenses/>.
 */

using System.Collections.Generic;
using System.IO;
using System.Reflection;
using Newtonsoft.Json;

namespace Storm.ExternalEvent
{
    public class LocalModLoader : AssemblyModLoader
    {
        private readonly string _path;

        public LocalModLoader(string path = "./")
        {
            _path = path;
        }

        public override List<LoadedMod> Load()
        {
            var dirs = Directory.GetDirectories(_path);
            var result = new List<LoadedMod>();
            foreach (var str in dirs)
            {
                LoadMod(result, str);
            }
            return result;
        }

        private void LoadMod(List<LoadedMod> result, string path)
        {
            var manifestPath = Path.Combine(path, "manifest.json");

            /* I thought about allowing mods without manifests, but it's unnecessary */
            /* just include a manifest.json with ur mods gee - Handsome Matt */
            if (!File.Exists(manifestPath))
                return;

            var manifest = JsonConvert.DeserializeObject<JsonModManifest>(File.ReadAllText(manifestPath));

            if (manifest.Properties != null && manifest.Properties.Path == null)
            {
                manifest.Properties.Path = path;
            }

            var dllPath = string.Empty;
            if (!string.IsNullOrEmpty(manifest.AssemblyFileName))
                dllPath = Path.Combine(path, manifest.AssemblyFileName);

            /* if we have an assembly to load, let's do it */
            var assemblyMods = new List<AssemblyMod>();
            if (!string.IsNullOrEmpty(dllPath) && File.Exists(dllPath))
            {
                var loaded = LoadModsFromAssembly(Assembly.UnsafeLoadFrom(dllPath));
                loaded.ForEach(m => m.LoadDirectory = path);

                assemblyMods.AddRange(loaded);
            }

            var mod = new LoadedMod(manifest, assemblyMods);
            result.Add(mod);

            Logging.DebugLogs("[{0}] Loaded mod {1} {3} by {2}", GetType().Name, mod.Name, mod.Author, mod.Version);
        }
    }
}