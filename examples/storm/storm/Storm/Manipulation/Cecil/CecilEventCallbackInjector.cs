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

using System.Collections.Generic;
using System.Linq;
using Mono.Cecil;
using Mono.Cecil.Cil;
using Storm.StardewValley;
using Storm.StardewValley.Event;

namespace Storm.Manipulation.Cecil
{
    public class CecilEventCallbackInjector : IInjector
    {
        private readonly AssemblyDefinition _def;

        private readonly List<Instruction> _injectionPoints = new List<Instruction>();
        private readonly EventCallbackParams _params;
        private readonly AssemblyDefinition _self;
        private MethodDefinition _injectee;
        private bool _invalid;

        public CecilEventCallbackInjector(AssemblyDefinition self, AssemblyDefinition def, EventCallbackParams @params)
        {
            _self = self;
            _def = def;
            _params = @params;
        }

        public void Init()
        {
            _injectee = _def.GetMethod(_params.OwnerType, _params.OwnerMethodName, _params.OwnerMethodDesc);
            if (_injectee == null)
            {
                Logging.DebugLogs("[{0}] Could not find injectee!", GetType().Name);
                Logging.DebugLogs("\t{0} {1} {2}", _params.OwnerType, _params.OwnerMethodName, _params.OwnerMethodDesc);
                Logging.DebugLogs("\t{0}", _params.InsertionIndex);
                _invalid = true;
                return;
            }

            var injecteeBody = _injectee.Body;
            var injecteeInstructions = injecteeBody.Instructions;
            var injecteeInsCount = injecteeInstructions.Count;
            if (_params.InsertionType == InsertionType.Beginning)
            {
                _injectionPoints.Add(injecteeInstructions[0]);
                return;
            }

            if (_params.InsertionType == InsertionType.Last && _params.InsertionIndex == null)
            {
                _injectionPoints.Add(injecteeInstructions[injecteeInsCount - 1]);
                return;
            }

            foreach (var i in _params.InsertionIndex)
            {
                switch (_params.InsertionType)
                {
                    case InsertionType.Absolute:
                        if (i < 0 || i >= injecteeInsCount)
                        {
                            Logging.DebugLogs("[{0}] Instruction {1} out of bounds", GetType().Name, i);
                            Logging.DebugLogs("\t{0} {1} {2}", _params.OwnerType, _params.OwnerMethodName, _params.OwnerMethodDesc);
                            Logging.DebugLogs("\t{0}", _params.InsertionIndex);
                            _invalid = true;
                            return;
                        }

                        _injectionPoints.Add(injecteeInstructions[i]);
                        break;

                    case InsertionType.Last:
                        if (injecteeInsCount - 1 - i < 0 || injecteeInsCount - 1 - i >= injecteeInsCount)
                        {
                            Logging.DebugLogs("[{0}] Instruction {1} out of bounds", GetType().Name, i);
                            Logging.DebugLogs("\t{0} {1} {2}", _params.OwnerType, _params.OwnerMethodName, _params.OwnerMethodDesc);
                            Logging.DebugLogs("\t{0}", _params.InsertionIndex);
                            _invalid = true;
                            return;
                        }

                        _injectionPoints.Add(injecteeInstructions[injecteeInsCount - 1 - i]);
                        break;

                    case InsertionType.Returns:
                        var relative = GetReturnByRelativity(_injectee, i);
                        if (relative == null)
                        {
                            Logging.DebugLogs("[{0}] Unable to find return {1}", GetType().Name, i);
                            Logging.DebugLogs("\t{0} {1} {2}", _params.OwnerType, _params.OwnerMethodName, _params.OwnerMethodDesc);
                            Logging.DebugLogs("\t{0}", _params.InsertionIndex);
                            _invalid = true;
                            return;
                        }
                        _injectionPoints.Add(relative);
                        break;
                }
            }
        }

        private Instruction setIfNull(ref Instruction target, Instruction ins)
        {
            if (target == null)
            {
                target = ins;
            }
            return ins;
        }

        public void Inject()
        {
            if (_invalid) return;

            var hasReturnValue = typeof(DetourEvent).GetProperty("ReturnEarly");
            var hasReturnValueImport = _def.Import(hasReturnValue.GetMethod);

            var eventReturnValue = typeof(DetourEvent).GetProperty("ReturnValue");
            var eventReturnValueImport = _def.Import(eventReturnValue.GetMethod);

            var wrapperMethod = typeof(StaticGameContext).GetMethod("Wrap");
            var wrapperMethodImport = _def.Import(wrapperMethod);

            var fireEventMethod = typeof(StaticGameContext).GetMethod("FireEvent");
            var fireEventMethodImport = _def.Import(fireEventMethod);

            var createEventMethod = typeof(StaticContextEvent).GetConstructor(new[] { typeof(object[]) });
            var createEventMethodImport = _def.Import(createEventMethod);

            var body = _injectee.Body;
            var processor = body.GetILProcessor();

            var returnName = _injectee.ReturnType.FullName;
            var returnsVoid = returnName.Equals(typeof(void).FullName);
            var returnsPrimitive = CecilUtils.IsNativeType(returnName);

            var paramCount = 0;
            if (_params.PushParams)
            {
                paramCount += _injectee.Parameters.Count;
            }

            if (!_injectee.IsStatic)
            {
                paramCount++;
            }

            foreach (var injectionPoint in _injectionPoints)
            {
                var jmpTarget = returnsVoid ? injectionPoint : processor.Create(OpCodes.Pop);

                Instruction initial = null;

                var eventId = setIfNull(ref initial, processor.Create(OpCodes.Ldstr, _params.EventId));
                processor.InsertBefore(injectionPoint, eventId);

                var arraySize = setIfNull(ref initial, processor.Create(OpCodes.Ldc_I4, paramCount));
                processor.InsertBefore(injectionPoint, arraySize);

                var arrayCreator = setIfNull(ref initial, processor.Create(OpCodes.Newarr, _def.MainModule.Import(typeof(object))));
                processor.InsertBefore(injectionPoint, arrayCreator);

                var arrayPointer = 0;

                for (var i = 0; i < paramCount; i++)
                {
                    var dupIns = setIfNull(ref initial, processor.Create(OpCodes.Dup));
                    processor.InsertBefore(injectionPoint, dupIns);
                }

                if (!_injectee.IsStatic)
                {
                    processor.InsertBefore(injectionPoint, setIfNull(ref initial, processor.Create(OpCodes.Ldc_I4, arrayPointer++)));
                    processor.InsertBefore(injectionPoint, setIfNull(ref initial, processor.Create(OpCodes.Ldarg_0)));
                    processor.InsertBefore(injectionPoint, setIfNull(ref initial, processor.Create(OpCodes.Call, wrapperMethodImport)));
                    processor.InsertBefore(injectionPoint, setIfNull(ref initial, processor.Create(OpCodes.Stelem_Ref)));
                }

                if (_params.PushParams)
                {
                    for (var i = 0; i < _injectee.Parameters.Count; i++)
                    {
                        var param = _injectee.Parameters[i];

                        processor.InsertBefore(injectionPoint, processor.Create(OpCodes.Ldc_I4, arrayPointer++));
                        processor.InsertBefore(injectionPoint, setIfNull(ref initial, processor.Create(OpCodes.Ldarg, i + (_injectee.IsStatic ? 0 : 1))));
                        processor.InsertBefore(injectionPoint, CecilUtils.IsNativeType(param.ParameterType) ? processor.Create(OpCodes.Box, param.ParameterType) : processor.Create(OpCodes.Call, wrapperMethodImport));
                        processor.InsertBefore(injectionPoint, processor.Create(OpCodes.Stelem_Ref));
                    }
                }

                var ctorCall = setIfNull(ref initial, processor.Create(OpCodes.Newobj, createEventMethodImport));
                processor.InsertBefore(injectionPoint, ctorCall);

                var callbackCall = setIfNull(ref initial, processor.Create(OpCodes.Call, fireEventMethodImport));
                processor.InsertBefore(injectionPoint, callbackCall);

                if (!returnsVoid)
                {
                    processor.InsertBefore(injectionPoint, processor.Create(OpCodes.Dup));
                }
                processor.InsertBefore(injectionPoint, processor.Create(OpCodes.Call, hasReturnValueImport));

                var continueNormalJump = processor.Create(OpCodes.Brfalse, jmpTarget);
                processor.InsertBefore(injectionPoint, continueNormalJump);

                if (!returnsVoid)
                {
                    processor.InsertBefore(injectionPoint, processor.Create(OpCodes.Call, eventReturnValueImport));
                }

                if (returnsPrimitive)
                {
                    processor.InsertBefore(injectionPoint, processor.Create(OpCodes.Unbox_Any, _injectee.ReturnType));
                }

                processor.InsertBefore(injectionPoint, processor.Create(OpCodes.Ret));
                if (!returnsVoid)
                {
                    processor.InsertBefore(injectionPoint, jmpTarget);
                }

                if (_params.RedirectBranching)
                {
                    foreach (var instruction in body.Instructions.Where(i => i != continueNormalJump))
                    {
                        if (CecilUtils.IsJump(instruction.OpCode))
                        {
                            if (instruction.Operand == injectionPoint)
                            {
                                instruction.Operand = initial;
                            }
                        }
                    }
                }
            }
        }

        private Instruction GetReturnByRelativity(MethodDefinition md, int index)
        {
            var instructions = md.Body.Instructions;
            var counter = 0;
            foreach (var ins in instructions)
            {
                if (ins.OpCode == OpCodes.Ret)
                {
                    if (counter == index)
                    {
                        return ins;
                    }
                    counter++;
                }
            }
            return null;
        }

        public object GetParams()
        {
            return _params;
        }
    }
}