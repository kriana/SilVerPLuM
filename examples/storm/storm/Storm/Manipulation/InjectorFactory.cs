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
using System.IO;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Storm.Manipulation.Json;

namespace Storm.Manipulation
{
    public abstract class InjectorFactory
    {
        protected InjectorFactory()
        {
        }

        protected InjectorFactory(string path)
        {
            UpdatePath(path);
        }

        protected abstract void UpdatePath(string path);

        public IInjector CreateClassInfoInjector(ClassInfoParams @params)
        {
            return new ClassInfoInjector(@params);
        }

        public virtual IInjector CreateFieldInfoInjector(FieldInfoParams @params)
        {
            return new FieldInfoInjector(@params);
        }

        public virtual IInjector CreateMethodInfoInjector(MethodInfoParams @params)
        {
            return new MethodInfoInjector(@params);
        }

        public abstract IInjector CreateFieldDetourInjector(FieldDetourParams @params);

        public abstract IInjector CreateFieldAccessorMutatorInjector(FieldAccessorMutatorParams @params);

        public abstract IInjector CreateInvokerInjector(InvokerParams @params);

        public abstract IInjector CreateEventCallbackInjector(EventCallbackParams @params);

        public abstract Assembly ToConcrete();

        public InjectionFactoryContext ParseOfType(DataFormat format, string path)
        {
            var ctx = new InjectionFactoryContext {Injectors = new List<IInjector>()};

            switch (format)
            {
                case DataFormat.Json:
                    ctx.Injectors = ParseJson(path);
                    break;
                case DataFormat.Xml:
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(format), format, null);
            }

            ctx.GetConcreteAssembly = ToConcrete;
            return ctx;
        }

        private List<IInjector> ParseJson(string path)
        {
            var list = new List<IInjector>();
            var nameMap = new Dictionary<string, string>();

            var primary = Path.Combine(path, "interface_injectors.json");
            ParseJson(new FileStream(primary, FileMode.Open, FileAccess.Read), list, nameMap);

            var secondaryFolder = Path.Combine(path, "secondary\\");
            foreach (var child in Directory.GetFiles(secondaryFolder, "*"))
            {
                ParseJson(new FileStream(child, FileMode.Open, FileAccess.Read), list, nameMap);
            }

            Logging.DebugLogs("[{0}] Loaded {1} injectors.", GetType().Name, list.Count);
            return list;
        }

        private void ParseJson(Stream @in, List<IInjector> list, Dictionary<string, string> nameMap)
        {
            var reader = new StreamReader(@in);
            var json = reader.ReadToEnd();
            reader.Close();

            var container = JsonConvert.DeserializeObject<JsonParamContainer>(json);
            if (container == null) return;

            foreach (var param in container.ClassInfoParams)
            {
                list.Add(CreateClassInfoInjector(new ClassInfoParams {SimpleName = param.SimpleName, OwnerType = param.OwnerType}));
                nameMap.Add(param.SimpleName, param.OwnerType);
            }

            // FIXME - There has got to be a better way to do everything under this
            list.AddRange(container.FieldDetourParams.Select(injector => CreateFieldDetourInjector(new FieldDetourParams
            {
                OwnerType = InjectorMetaData.FilterTags(nameMap, injector.OwnerAccessorType),
                OwnerFieldName = injector.OwnerFieldName,
                OwnerFieldType = InjectorMetaData.FilterTags(nameMap, injector.OwnerFieldType),
                DetourType = InjectorMetaData.FilterTags(nameMap, injector.DetourType),
                DetourMethodName = injector.DetourMethodName,
                DetourMethodDesc = injector.DetourMethodDesc
            })));


            list.AddRange(container.FieldAccessorMutatorParams.Select(injector => CreateFieldAccessorMutatorInjector(new FieldAccessorMutatorParams
            {
                OwnerType = InjectorMetaData.FilterTags(nameMap, injector.OwnerAccessorType),
                OwnerFieldName = injector.OwnerFieldName,
                OwnerFieldType = InjectorMetaData.FilterTags(nameMap, injector.OwnerFieldType),
                MethodName = injector.MethodName,
                IsStatic = injector.IsStatic,
                OwnerAccessorType = injector.OwnerAccessorType
            })));

            list.AddRange(container.InvokerParams.Select(injector => CreateInvokerInjector(new InvokerParams {
                OwnerType = InjectorMetaData.FilterTags(nameMap, injector.OwnerAccessorType),
                OwnerMethodName = injector.OwnerMethodName,
                OwnerMethodDesc = InjectorMetaData.FilterTags(nameMap, injector.OwnerMethodDesc),
                InvokerType = injector.InvokerType == null ? null : InjectorMetaData.FilterTags(nameMap, injector.InvokerType),
                InvokerName = injector.InvokerName, IsStatic = injector.IsStatic
            })));

            list.AddRange(container.FieldInfoParams.Select(injector => CreateFieldInfoInjector(new FieldInfoParams
            {
                OwnerType = InjectorMetaData.FilterTags(nameMap, injector.OwnerAccessorType),
                FieldName = injector.FieldName,
                FieldType = InjectorMetaData.FilterTags(nameMap, injector.FieldType),
                OwnerAccessorType = injector.OwnerAccessorType,
                RefactoredName = injector.RefactoredName
            })));

            list.AddRange(container.MethodInfoParams.Select(injector => CreateMethodInfoInjector(new MethodInfoParams
            {
                OwnerType = InjectorMetaData.FilterTags(nameMap, 
                injector.OwnerAccessorType),
                MethodName = injector.MethodName,
                MethodDesc = InjectorMetaData.FilterTags(nameMap, injector.MethodDesc),
                OwnerAccessorType = injector.OwnerAccessorType,
                RefactoredName = injector.RefactoredName
            })));

            list.AddRange(container.EventCallbackParams.Select(injector => CreateEventCallbackInjector(new EventCallbackParams
            {
                OwnerType = InjectorMetaData.FilterTags(nameMap, 
                injector.OwnerAccessorType),
                OwnerMethodName = injector.OwnerMethodName,
                OwnerMethodDesc = InjectorMetaData.FilterTags(nameMap, injector.OwnerMethodDesc),
                EventId = injector.EventId,
                InsertionIndex = injector.InsertionIndex,
                InsertionType = injector.InsertionType,
                PushParams = injector.PushParams,
                RedirectBranching = injector.RedirectBranching
            })));
        }
    }
}