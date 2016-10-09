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
using System.Reflection;
using Mono.Cecil;

namespace Storm.Manipulation.Cecil
{
    public class CecilInjectorFactory : InjectorFactory
    {
        private Assembly _refAssembly;

        public CecilInjectorFactory()
        {
        }

        public CecilInjectorFactory(string path) : base(path)
        {
        }

        public AssemblyDefinition SelfAssembly { get; private set; }
        public AssemblyDefinition GameAssembly { get; private set; }

        private void CheckSelf()
        {
            if (SelfAssembly == null)
            {
                SelfAssembly = AssemblyDefinition.ReadAssembly("StormLoader.exe");
            }
        }

        protected override void UpdatePath(string path)
        {
            GameAssembly = AssemblyDefinition.ReadAssembly(path);
        }

        public override IInjector CreateFieldDetourInjector(FieldDetourParams @params)
        {
            CheckSelf();
            return new CecilFieldDetourInjector(SelfAssembly, GameAssembly, @params);
        }

        public override IInjector CreateFieldAccessorMutatorInjector(FieldAccessorMutatorParams @params)
        {
            CheckSelf();
            return new CecilFieldAccessorMutatorInjector(SelfAssembly, GameAssembly, @params);
        }

        public override IInjector CreateInvokerInjector(InvokerParams @params)
        {
            CheckSelf();
            return new CecilInvokerInjector(SelfAssembly, GameAssembly, @params);
        }

        public override IInjector CreateEventCallbackInjector(EventCallbackParams @params)
        {
            CheckSelf();
            return new CecilEventCallbackInjector(SelfAssembly, GameAssembly, @params);
        }

        public override Assembly ToConcrete()
        {
            if (_refAssembly != null) return _refAssembly;
            using (var strum = new MemoryStream())
            {
                GameAssembly.Name.Name = "Storm-Hooked-Game";
                GameAssembly.Write(strum);
                using (var strum2 = new FileStream("Storm-Hooked-Game.exe", FileMode.Create, FileAccess.Write))
                {
                    GameAssembly.Write(strum2);
                }

                var domain = AppDomain.CreateDomain("Game Domain");
                domain.UnhandledException += Logging.UnhandledExceptionHandler;
                _refAssembly = domain.Load(strum.GetBuffer());
            }
            return _refAssembly;
        }

        public void WriteModifiedAssembly(Stream @out)
        {
            GameAssembly.Write(@out);
        }
    }
}