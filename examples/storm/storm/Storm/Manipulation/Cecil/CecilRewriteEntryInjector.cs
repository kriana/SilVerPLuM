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
using System.Linq;
using Mono.Cecil;
using Mono.Cecil.Cil;

namespace Storm.Manipulation.Cecil
{
    public class CecilRewriteEntryInjector : IInjector
    {
        private readonly AssemblyDefinition _def;
        private readonly RewriteEntryInjectorParams _params;
        private AssemblyDefinition _self;

        public CecilRewriteEntryInjector(AssemblyDefinition self, AssemblyDefinition def, RewriteEntryInjectorParams @params)
        {
            _self = self;
            _def = def;
            _params = @params;
        }

        public void Init()
        {
        }

        public void Inject()
        {
            var entry = _def.EntryPoint.DeclaringType;
            entry.Attributes = TypeAttributes.Class | TypeAttributes.AutoLayout | TypeAttributes.BeforeFieldInit | TypeAttributes.Public | TypeAttributes.AnsiClass;

            var hasConstructor = entry.Methods.SingleOrDefault(m => m.Name.Equals(".ctor")) != null;
            if (!hasConstructor)
            {
                var method = new MethodDefinition(".ctor", MethodAttributes.SpecialName | MethodAttributes.HideBySig | MethodAttributes.Family | MethodAttributes.Public | MethodAttributes.ReuseSlot | MethodAttributes.RTSpecialName, entry.Module.Import(typeof(void)));

                var processor = method.Body.GetILProcessor();
                processor.Append(processor.Create(OpCodes.Ldarg_0));
                processor.Append(processor.Create(OpCodes.Call, entry.Module.Import(typeof(object).GetConstructor(new Type[0]))));
                processor.Append(processor.Create(OpCodes.Ret));
                entry.Methods.Add(method);
            }
        }

        public object GetParams()
        {
            return _params;
        }
    }
}