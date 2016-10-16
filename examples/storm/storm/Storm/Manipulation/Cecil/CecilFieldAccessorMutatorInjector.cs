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

using Mono.Cecil;
using Mono.Cecil.Cil;

namespace Storm.Manipulation.Cecil
{
    public class CecilFieldAccessorMutatorInjector : IInjector
    {
        private readonly AssemblyDefinition _def;
        private FieldAccessorMutatorParams _params;
        private AssemblyDefinition _self;

        public CecilFieldAccessorMutatorInjector(AssemblyDefinition self, AssemblyDefinition def, FieldAccessorMutatorParams @params)
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
            var field = _def.GetField(_params.OwnerType, _params.OwnerFieldName, _params.OwnerFieldType);
            if (field == null)
            {
                Logging.DebugLogs("[{0}] Could not find field!", GetType().Name);
                Logging.DebugLogs("\t{0} {1} {2}", _params.OwnerType, _params.OwnerFieldName, _params.OwnerFieldType);
                Logging.DebugLogs("\t{0}", _params.MethodName);
                return;
            }

            var mutator = new MethodDefinition("_Set" + _params.MethodName, MethodAttributes.Public | MethodAttributes.NewSlot | MethodAttributes.Virtual, _def.Import(typeof(void)));
            {
                mutator.Parameters.Add(new ParameterDefinition(_def.Import(typeof(object))));

                var instructions = mutator.Body.Instructions;
                var processor = mutator.Body.GetILProcessor();
                if (!_params.IsStatic)
                {
                    instructions.Add(processor.Create(OpCodes.Ldarg_0));
                }
                instructions.Add(processor.Create(_params.IsStatic ? OpCodes.Ldarg_0 : OpCodes.Ldarg_1));
                instructions.Add(processor.Create(OpCodes.Stfld, field));
                instructions.Add(processor.Create(OpCodes.Ret));
            }

            var accessor = new MethodDefinition("_Get" + _params.MethodName, MethodAttributes.Public | MethodAttributes.NewSlot | MethodAttributes.Virtual, _def.Import(typeof(object)));
            {
                var instructions = accessor.Body.Instructions;
                var processor = accessor.Body.GetILProcessor();
                if (!_params.IsStatic)
                {
                    instructions.Add(processor.Create(OpCodes.Ldarg_0));
                }
                instructions.Add(processor.Create(OpCodes.Ldfld, field));
                instructions.Add(processor.Create(OpCodes.Ret));
            }

            field.DeclaringType.Methods.Add(mutator);
            field.DeclaringType.Methods.Add(accessor);
        }

        public object GetParams()
        {
            return _params;
        }
    }
}