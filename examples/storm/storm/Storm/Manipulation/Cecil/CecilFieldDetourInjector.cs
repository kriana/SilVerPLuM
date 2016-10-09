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
    public class CecilFieldDetourInjector : IInjector
    {
        private readonly AssemblyDefinition _def;
        private readonly AssemblyDefinition _self;
        private FieldDetourParams _params;

        public CecilFieldDetourInjector(AssemblyDefinition self, AssemblyDefinition def, FieldDetourParams @params)
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
            var callingDefinition = _self.GetMethod(_params.DetourType, _params.DetourMethodName, _params.DetourMethodDesc) ?? _def.GetMethod(_params.DetourType, _params.DetourMethodName, _params.DetourMethodDesc);

            if (callingDefinition == null)
            {
                Logging.DebugLogs("[{0}] Could not find callingDefinition!", GetType().Name);
                Logging.DebugLogs("\t{0} {1} {2}", _params.OwnerType, _params.OwnerFieldName, _params.OwnerFieldType);
                Logging.DebugLogs("\t{0} {1} {2}", _params.DetourType, _params.DetourMethodName, _params.DetourMethodDesc);
                return;
            }

            var fieldRef = _def.GetField(_params.OwnerType, _params.OwnerFieldName, _params.OwnerFieldType);
            if (fieldRef == null)
            {
                Logging.DebugLogs("[{0}] Could not find fieldRef!", GetType().Name);
                Logging.DebugLogs("\t{0} {1} {2}", _params.OwnerType, _params.OwnerFieldName, _params.OwnerFieldType);
                Logging.DebugLogs("\t{0} {1} {2}", _params.DetourType, _params.DetourMethodName, _params.DetourMethodDesc);
                return;
            }

            var methods = _def.FindRefences(fieldRef, callingDefinition);
            foreach (var method in methods)
            {
                var import = method.Module.Import(callingDefinition.Resolve());
                var processor = method.Body.GetILProcessor();
                var instructions = method.Body.Instructions;
                for (var i = 0; i < instructions.Count; i++)
                {
                    var ins = instructions[i];
                    if (CecilUtils.IsGettingField(ins) && ins.Operand is FieldReference)
                    {
                        var casted = (FieldReference) ins.Operand;
                        if (casted.Resolve() == fieldRef.Resolve())
                        {
                            instructions[i] = processor.Create(OpCodes.Call, import);
                        }
                    }
                }
            }
        }

        public object GetParams()
        {
            return _params;
        }
    }
}