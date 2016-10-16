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

using System.Linq;
using Mono.Cecil;
using Mono.Cecil.Cil;

namespace Storm.Manipulation.Cecil
{
    public class CecilInstanceDetourInjector : IInjector
    {
        private readonly AssemblyDefinition _def;
        private readonly ConstructorReplacerParams _params;
        private readonly AssemblyDefinition _self;

        public CecilInstanceDetourInjector(AssemblyDefinition self, AssemblyDefinition def, ConstructorReplacerParams @params)
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
            var from = _def.GetTypeRef(_params.FromClass) ?? _self.GetTypeRef(_params.FromClass, true);

            if (from == null)
            {
                Logging.DebugLogs("[{0}] Unable to find from type", GetType().Name);
                Logging.DebugLogs("\t{0} {1}", _params.FromClass, _params.ToClass);
                return;
            }

            var to = _def.GetTypeRef(_params.ToClass) ?? _self.GetTypeRef(_params.ToClass, true);

            if (to == null)
            {
                Logging.DebugLogs("[{0}] Unable to find to type", GetType().Name);
                Logging.DebugLogs("\t{0} {1}", _params.FromClass, _params.ToClass);
                return;
            }

            var methods = _def.Modules.SelectMany(m => m.Types).SelectMany(t => t.Methods).Where(m => m.HasBody).ToList();

            foreach (var method in methods)
            {
                var body = method.Body;
                var instructions = body.Instructions;
                var processor = body.GetILProcessor();

                for (int i = 0; i < instructions.Count; i++)
                {
                    Instruction ins = instructions[i];
                    if (ins.OpCode == OpCodes.Call || ins.OpCode == OpCodes.Callvirt)
                    {
                        var @ref = (MethodReference)ins.Operand;
                        if (@ref.DeclaringType.FullName.Equals(_params.FromClass))
                        {
                            var redirect = to.Resolve().Methods.FirstOrDefault(m => m.Name.Equals(@ref.Name) && @ref.Parameters.Count + 1 == m.Parameters.Count);
                            if (redirect != null)
                            {
                                var call = _def.Import(redirect);
                                var gim = @ref as GenericInstanceMethod;
                                if (gim != null)
                                {
                                    var genericCall = new GenericInstanceMethod(_def.Import(redirect));
                                    foreach (var arg in gim.GenericArguments)
                                    {
                                        genericCall.GenericArguments.Add(arg);
                                    }
                                    call = genericCall;
                                }

                                processor.Replace(ins, processor.Create(OpCodes.Call, call));
                            }
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