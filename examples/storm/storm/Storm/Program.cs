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
using System.Windows.Forms;
using Microsoft.Xna.Framework;
using Storm.Collections;
using Storm.StardewValley;
using Storm.StardewValley.Wrapper;

namespace Storm
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            if (Environment.OSVersion.Platform == PlatformID.Unix || Environment.OSVersion.Platform == PlatformID.MacOSX)
                Environment.SetEnvironmentVariable("FNA_WORKAROUND_WINDOW_RESIZABLE", "1");

#if DEBUG
            Logging.Log = Console.WriteLine;
            Logging.DebugLog = Console.WriteLine;
#else
            Logging.Log = Logging.LogToFile;
            Logging.DebugLog = Logging.LogToFile;
#endif

            AppDomain.CurrentDomain.UnhandledException += Logging.UnhandledExceptionHandler;

            var launcher = new ManagedStardewValleyLauncher("Stardew Valley.exe", true);
            launcher.Launch();
        }
    }
}