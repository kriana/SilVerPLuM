/*
    Copyright 2016 Cody R. (Demmonic), Zoey (Zoryn), Matt Stevens (Handsome Matt), Matthew Bell (mdbell), Inari-Whitebear

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
using Storm.ExternalEvent;
using Storm.Manipulation;
using Storm.StardewValley.Event;
using Storm.StardewValley.Wrapper;

namespace Storm.StardewValley
{
    public static class StaticGameContext
    {
        private static readonly Dictionary<Type, Type> CachedAccessorWrapperTypes = new Dictionary<Type, Type>();
        private static List<IInjector> Injectors { get; set; }
        private static Dictionary<Type, object> CachedFactories { get; set; } = new Dictionary<Type, object>();
        private static List<Type> CachedWrappers { get; set; }
        private static Assembly Assembly { get; set; }

        private static ProgramWrapper Root { get; set; }

        private static EventBus EventBus { get; set; }

        private static StaticContext WrappedGame => Root.GetGame();

        public static void Init(Assembly assembly, ProgramWrapper root, EventBus eventBus, List<IInjector> injectors)
        {
            Assembly = assembly;
            Root = root;
            EventBus = eventBus;
            Injectors = injectors;
        }

        private static void InitializeEvent(StaticContextEvent @event)
        {
            @event.GameAssembly = Assembly;
            @event.Root = WrappedGame;
            @event.EventBus = EventBus;
        }

        private static DetourEvent HookEvent(DetourEvent @event)
        {
            (@event as StaticContextEvent)?.Init(InitializeEvent);
            return @event;
        }

        public static DetourEvent FireEvent(string name, DetourEvent @event)
        {
            HookEvent(@event);
            EventBus.Fire(name, @event);
            return @event;
        }

        public static bool IsSubclass(object o, string name)
        {
            var t = InjectorMetaData.TypeForSimpleName(Injectors, name);
            return t.IsInstanceOfType(o);
        }

        private static List<Type> GetWrappers()
        {
            return CachedWrappers ?? (CachedWrappers = ReflectionUtils.DynamicResolveAll("Storm.StardewValley.Wrapper."));
        }

        private static Type WrapperForSimpleName(string name)
        {
            var types = GetWrappers();
            foreach (var type in types)
            {
                var attr = type.GetCustomAttribute(typeof(WrappedAccessor));
                if (attr == null) continue;

                if (((WrappedAccessor) attr).SimpleName == name)
                {
                    return type;
                }
            }
            return null;
        }

        public static object Wrap(object o)
        {
            if (o == null)
            {
                return null;
            }

            var cur = o.GetType();
            while (cur != null && cur != typeof(object))
            {
                Type type;
                CachedAccessorWrapperTypes.TryGetValue(cur, out type);
                if (type == null)
                {
                    var name = InjectorMetaData.TypeToSimpleName(Injectors, cur);
                    if (name != null)
                    {
                        type = WrapperForSimpleName(name);
                    }
                }

                if (type != null)
                {
                    var instance = Activator.CreateInstance(type);

                    var wrapper = instance as Wrapper.Wrapper;
                    if (wrapper != null)
                    {
                        wrapper.Underlying = o;
                    }

                    var swrapper = instance as StaticContextWrapper;
                    if (swrapper != null)
                    {
                        swrapper.Parent = WrappedGame;
                    }

                    if (!CachedAccessorWrapperTypes.ContainsKey(cur))
                    {
                        CachedAccessorWrapperTypes.Add(cur, type);
                    }
                    return instance;
                }
                cur = cur.BaseType;
            }
            return o;
        }
    }
}