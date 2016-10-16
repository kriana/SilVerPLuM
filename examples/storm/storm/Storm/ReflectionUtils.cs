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
using System.Text;

namespace Storm
{
    public static class ReflectionUtils
    {
        public static string DescriptionOf(MethodInfo md)
        {
            var sb = new StringBuilder();
            sb.Append('(');

            var set = false;
            foreach (var param in md.GetParameters())
            {
                sb.Append(param.ParameterType.FullName);
                sb.Append(',');
                set = true;
            }
            if (set) sb.Length -= 1;

            sb.Append(')');
            sb.Append(md.ReturnType.FullName);
            return sb.ToString();
        }

        public static Type DynamicResolve(string name)
        {
            return AppDomain.CurrentDomain.GetAssemblies().SelectMany(a => a.GetTypes()).FirstOrDefault(t => t.FullName.Equals(name));
        }

        public static List<Type> DynamicResolveAll(string substring)
        {
            return AppDomain.CurrentDomain.GetAssemblies().SelectMany(a => a.GetTypes()).Where(t => t.FullName.Contains(substring)).ToList();
        }
    }
}