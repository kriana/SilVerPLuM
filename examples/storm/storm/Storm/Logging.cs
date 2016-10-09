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
using System.Windows.Forms;
using Storm.StardewValley;

namespace Storm
{
    public static class Logging
    {
        public delegate void Logger(string msg);

        public static Logger Log = s => { };
        public static Logger DebugLog = s => { };

        public static UnhandledExceptionEventHandler UnhandledExceptionHandler = (s, e) =>
        {
            LogToFile(e.ExceptionObject.ToString());
            MessageBox.Show("Your game seems to have crashed! We've generated a crash log for you in\n" + StormApi.GetResource("storm_log.txt"), "Oh no!");
        };

        public static void LogToFile(string s)
        {
            var @out = StormApi.GetResource("storm_log.txt");
            var sr = new StreamWriter(@out, true);
            sr.WriteLine(s);
            sr.Close();
        }

        public static void Logs(string format, params object[] values)
        {
            Log(string.Format(format, values));
        }

        public static void DebugLogs(string format, params object[] values)
        {
            DebugLog(string.Format(format, values));
        }
    }
}