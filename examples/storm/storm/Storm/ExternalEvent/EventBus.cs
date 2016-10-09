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
using System.Reflection;
using Storm.Manipulation;

namespace Storm.ExternalEvent
{
    public class EventBus
    {
        private readonly Dictionary<string, List<ReceiverSwitch>> _receivers = new Dictionary<string, List<ReceiverSwitch>>();
        public List<LoadedMod> Mods = new List<LoadedMod>();

        public void AddReceiver(string eventType, ReceiverSwitch @switch)
        {
            List<ReceiverSwitch> list;
            if (!_receivers.TryGetValue(eventType, out list))
            {
                list = new List<ReceiverSwitch>();
                _receivers.Add(eventType, list);
            }

            var idx = -1;
            for (var i = 0; i < list.Count; i++)
            {
                if (@switch.Priority > list[i].Priority)
                {
                    idx = i;
                    break;
                }
            }

            @switch.Enabled = true;

            if (idx == -1) list.Add(@switch);
            else list.Insert(idx, @switch);
        }

        public void AddReceiver(object parent, string eventType, MethodInfo receiver, int priority)
        {
            AddReceiver(eventType, new ReceiverSwitch()
            {
                Instance = parent,
                Info = receiver,
                Priority = priority,
                Enabled = true,
            });
        }

        public void AddReceiver(LoadedMod mod)
        {
            foreach (var sub in mod.AssemblyMods)
            {
                foreach (var entry in sub.CallMap)
                {
                    foreach (var @switch in entry.Value)
                    {
                        AddReceiver(sub.Instance, entry.Key, @switch.Info, @switch.Priority);
                    }
                }
            }
            Mods.Add(mod);
        }

        public void RemoveReceiver(LoadedMod mod)
        {
            Mods.Remove(mod);
        }

        private void DisableSwitches(object instance)
        {
            foreach (var entry in _receivers)
            {
                foreach (var @switch in entry.Value)
                {
                    var tmp = @switch;
                    if (tmp.Instance.Equals(instance))
                    {
                        tmp.Enabled = false;
                    }
                }
            }
        }

        public void Fire<T>(string name, T val) where T : DetourEvent
        {
            List<ReceiverSwitch> list;
            if (!_receivers.TryGetValue(name, out list))
            {
                return;
            }

            foreach (var @switch in list)
            {
                var tmp = @switch;
                try
                {
                    tmp.Info.Invoke(tmp.Instance, new object[] {val});
                }
                catch (Exception e)
                {
                    DisableSwitches(tmp.Instance);
                }
            }
        }
    }
}