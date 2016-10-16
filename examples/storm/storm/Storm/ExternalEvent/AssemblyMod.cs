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
using System.Reflection;
using Storm.Manipulation;

namespace Storm.ExternalEvent
{
    public struct AssemblyMod
    {
        public LoadedMod ParentMod;

        public object Instance;
        public Dictionary<string, List<ReceiverSwitch>> CallMap;

        public AssemblyMod(LoadedMod parent, object instance, Dictionary<string, List<ReceiverSwitch>> callMap)
        {
            ParentMod = parent;
            Instance = instance;
            CallMap = callMap;
        }

        public string LoadDirectory
        {
            get
            {
                var resource = Instance as DiskResource;
                return resource != null ? resource.PathOnDisk : string.Empty;
            }
            set
            {
                var resource = Instance as DiskResource;
                if (resource != null) resource.PathOnDisk = value;
            }
        }
    }
}