/*
    Copyright 2016 Zoey (Zoryn)

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
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Storm.ExternalEvent;

namespace Storm
{
    public class Config
    {
        [JsonIgnore]
        public virtual JObject JObject { get; protected set; }

        [JsonIgnore]
        public virtual string ConfigLocation { get; protected set; }

        public static Config Instance => new Config();

        public static Config InitializeConfig(string configLocation, Config baseConfig)
        {
            if (baseConfig == null)
            {
                Console.WriteLine("A config must be instantiated before being passed to Initialize.\n\t" + configLocation);
                return null;
            }

            baseConfig.ConfigLocation = configLocation;
            return baseConfig.LoadConfig(baseConfig);
        }

        public virtual Config GenerateBaseConfig(Config baseConfig)
        {
            return null;
        }

        public virtual Config LoadConfig(Config baseConfig)
        {
            if (!File.Exists(baseConfig.ConfigLocation))
            {
                GenerateBaseConfig(baseConfig).WriteConfig();
            }
            else
            {
                var p = baseConfig.ConfigLocation;

                try
                {
                    var j = JObject.Parse(Encoding.UTF8.GetString(File.ReadAllBytes(baseConfig.ConfigLocation)));
                    baseConfig = (Config) j.ToObject(baseConfig.GetType());
                    baseConfig.ConfigLocation = p;
                    baseConfig.JObject = j;

                    baseConfig = UpdateConfig(baseConfig);
                    baseConfig.ConfigLocation = p;
                    baseConfig.JObject = j;

                    baseConfig.WriteConfig();
                }
                catch
                {
                    Console.WriteLine("Invalid JSON Renamed: " + p);
                    if (File.Exists(p))
                    {
                        File.Move(p, Path.Combine(Path.GetDirectoryName(p), Path.GetFileNameWithoutExtension(p) + "." + Guid.NewGuid() + ".json"));
                    }
                    GenerateBaseConfig(baseConfig).WriteConfig();
                }
            }

            return baseConfig;
        }

        public virtual Config UpdateConfig(Config baseConfig)
        {
            try
            {
                var b = JObject.FromObject(baseConfig.GenerateBaseConfig(baseConfig));
                var u = baseConfig.JObject;
                b.Merge(u);
                return (Config) b.ToObject(baseConfig.GetType());
            }
            catch (Exception ex)
            {
                Logging.DebugLog(ex.ToString());
            }
            return baseConfig;
        }

        public void WriteConfig()
        {
            var toWrite = Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(this, this.GetType(), Formatting.Indented, new JsonSerializerSettings()));
            if (!File.Exists(ConfigLocation) || !File.ReadAllBytes(ConfigLocation).SequenceEqual(toWrite))
            {
                File.WriteAllBytes(ConfigLocation, toWrite);
            }
        }

        public Config ReloadConfig()
        {
            return UpdateConfig(this);
        }
    }
}