/*
    Copyright 2016 Matt Stevens (Handsome Matt)

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

using System.ComponentModel;
using Newtonsoft.Json;

namespace Storm.ExternalEvent
{
    public class JsonModManifest
    {
        [DefaultValue("Unnamed Mod")]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Populate)]
        public string DisplayName { get; set; }

        [DefaultValue("Unknown")]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Populate)]
        public string Author { get; set; }

        [DefaultValue("1.0.0.0")]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Populate)]
        public string Version { get; set; }

        [DefaultValue("")]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Populate)]
        public string Description { get; set; }

        public string AssemblyFileName { get; set; }

        // a mapping of textures to load
        public dynamic Properties { get; set; }
    }
}