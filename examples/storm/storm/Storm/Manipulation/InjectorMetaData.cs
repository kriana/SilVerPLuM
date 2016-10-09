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

namespace Storm.Manipulation
{
    public static class InjectorMetaData
    {
        public static Type TypeForSimpleName(List<IInjector> list, string name)
        {
            foreach (var injector in list)
            {
                var @params = injector.GetParams();
                if (@params is ClassInfoParams)
                {
                    var casted = (ClassInfoParams) @params;
                    if (casted.SimpleName == name)
                    {
                        return ReflectionUtils.DynamicResolve(casted.OwnerType);
                    }
                }
            }
            return null;
        }

        public static string TypeToSimpleName(List<IInjector> list, Type t)
        {
            foreach (var injector in list)
            {
                var @params = injector.GetParams();
                if (@params is ClassInfoParams)
                {
                    var casted = (ClassInfoParams) @params;
                    if (casted.OwnerType == t.FullName)
                    {
                        return casted.SimpleName;
                    }
                }
            }
            return null;
        }

        public static string NameOfMethod(List<IInjector> list, string type, string refactored, string desc)
        {
            foreach (var injector in list)
            {
                var @params = injector.GetParams();
                if (@params is MethodInfoParams)
                {
                    var casted = (MethodInfoParams) @params;
                    if (casted.OwnerAccessorType == type && casted.RefactoredName == refactored && casted.MethodDesc == desc)
                    {
                        return casted.MethodName;
                    }
                }
            }
            return null;
        }

        public static string NameOfMethod<T>(List<IInjector> list, string refactored, string desc)
        {
            return NameOfMethod(list, typeof(T).FullName, refactored, desc);
        }

        public static string NameOfMethod(Type t, List<IInjector> list, string refactored, string desc)
        {
            return NameOfMethod(list, t.FullName, refactored, desc);
        }

        public static Dictionary<string, string> BuildTags(List<IInjector> injectors)
        {
            var nameMap = new Dictionary<string, string>();
            foreach (var injector in injectors)
            {
                var @params = injector.GetParams();
                if (@params is ClassInfoParams)
                {
                    var casted = (ClassInfoParams) @params;
                    nameMap.Add(casted.SimpleName, casted.OwnerType);
                }
            }
            return nameMap;
        }

        public static string FilterTags(Dictionary<string, string> map, string s)
        {
            while (s.IndexOf("@", StringComparison.Ordinal) != -1)
            {
                var start = s.IndexOf('@');
                if (s[start + 1] == '(')
                {
                    var end = s.IndexOf(')', start);
                    if (end == -1) end = s.Length;
                    else end += 1;
                    var key = s.Substring(start + 2, end - start - 3);
                    s = s.Replace(s.Substring(start, end - start), map[key]);
                }
                else
                {
                    var end = s.IndexOf(' ', start);
                    if (end == -1) end = s.Length;
                    else end += 1;
                    var key = s.Substring(start + 1, end - start - 1);
                    s = s.Replace(s.Substring(start, end - start), map[key]);
                }
            }
            return s;
        }

        public static string FilterTags(List<IInjector> injectors, string s)
        {
            return FilterTags(BuildTags(injectors), s);
        }
    }
}