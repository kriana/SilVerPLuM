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
using System.IO;

namespace Storm.StardewValley
{
    public static class StormApi
    {
        public static readonly string AppDataPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\";

        public static readonly string StardewPath = AppDataPath + "StardewValley\\";
        public static readonly string StormPath = StardewPath + "Storm\\";
        public static readonly string ModsPath = StardewPath + "Mods\\";

        public static string GetResource(string file)
        {
            if (!Directory.Exists(StormPath))
            {
                Directory.CreateDirectory(StormPath);
            }
            return Path.Combine(StormPath, file);
        }
    }
}
