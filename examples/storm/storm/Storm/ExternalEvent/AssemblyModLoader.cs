/*
    Copyright 2016 Cody R. (Demmonic)

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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace Storm.ExternalEvent
{
    public abstract class AssemblyModLoader : IModLoader
    {
        public abstract List<LoadedMod> Load();

        protected List<AssemblyMod> LoadModsFromAssembly(Assembly assembly)
        {
            var result = new List<AssemblyMod>();
            try
            {
                var mods = assembly.Modules.SelectMany(m => m.GetTypes()).Where(t => t.GetCustomAttribute(typeof(Mod)) != null);
                foreach (var mod in mods)
                {
                    var constructor = mod.GetConstructor(Type.EmptyTypes);
                    if (constructor == null)
                    {
                        Logging.DebugLogs("Unable to find empty constructor for mod {0}", mod.FullName);
                        continue;
                    }

                    var map = new Dictionary<string, List<ReceiverSwitch>>();
                    var asmmod = new AssemblyMod
                    {
                        Instance = constructor.Invoke(null),
                        CallMap = map
                    };

                    var handlers = mod.GetMethods().Where(m => m.GetCustomAttribute(typeof(Subscribe)) != null);
                    foreach (var handler in handlers)
                    {
                        var attr = (Subscribe) handler.GetCustomAttribute(typeof(Subscribe));

                        var @params = handler.GetParameters();
                        if (@params.Length != 1)
                        {
                            Logging.DebugLog("Invalid handler on " + mod.FullName + " " + handler.Name + " " + ReflectionUtils.DescriptionOf(handler));
                            continue;
                        }

                        List<ReceiverSwitch> list;
                        if (!map.TryGetValue(attr.Name, out list))
                        {
                            list = new List<ReceiverSwitch>();
                            map.Add(attr.Name, list);
                        }

                        list.Add(new ReceiverSwitch
                        {
                            Enabled = true,
                            Info = handler,
                            Instance = asmmod.Instance,
                            Priority = int.MaxValue + attr.CallPriority,
                        });
                    }

                    result.Add(asmmod);
                }
            }
            catch (Exception e)
            {
                Logging.Logs("[{0}] Failed to load mods from assembly {1} due to error {2}", GetType().Name, assembly.FullName, e.ToString());
            }

            return result;
        }
    }
}