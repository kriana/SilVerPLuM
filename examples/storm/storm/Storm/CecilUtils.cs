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

using System.Text;
using Mono.Cecil;
using Mono.Cecil.Cil;

namespace Storm
{
    public static class CecilUtils
    {
        public static string DescriptionOf(MethodDefinition md)
        {
            var sb = new StringBuilder();
            sb.Append('(');

            var set = false;
            foreach (var param in md.Parameters)
            {
                sb.Append(param.ParameterType.Resolve().FullName);
                sb.Append(',');
                set = true;
            }
            if (set) sb.Length -= 1;

            sb.Append(')');
            sb.Append(md.ReturnType.Resolve().FullName);
            return sb.ToString();
        }

        public static bool IsGettingField(Instruction ins)
        {
            return ins.OpCode == OpCodes.Ldfld || ins.OpCode == OpCodes.Ldflda;
        }

        public static bool IsPuttingField(Instruction ins)
        {
            return ins.OpCode == OpCodes.Stfld;
        }

        public static bool IsNativeType(string fullName)
        {
            return fullName.Equals(typeof(long).FullName) || fullName.Equals(typeof(ulong).FullName) || fullName.Equals(typeof(int).FullName) || fullName.Equals(typeof(uint).FullName) || fullName.Equals(typeof(short).FullName) || fullName.Equals(typeof(ushort).FullName) || fullName.Equals(typeof(byte).FullName) || fullName.Equals(typeof(bool).FullName);
        }

        public static bool IsNativeType(TypeReference @ref)
        {
            var hardRef = @ref.Resolve();
            return IsNativeType(hardRef.FullName) || hardRef.IsValueType;
        }

        public static bool IsJump(OpCode oc)
        {
            return oc == OpCodes.Br || oc == OpCodes.Br_S || oc == OpCodes.Brtrue || oc == OpCodes.Brtrue_S || oc == OpCodes.Brfalse || oc == OpCodes.Brfalse_S || oc == OpCodes.Bne_Un || oc == OpCodes.Bne_Un_S || oc == OpCodes.Blt_Un || oc == OpCodes.Blt_Un_S || oc == OpCodes.Ble_Un || oc == OpCodes.Ble_Un_S || oc == OpCodes.Bge_Un || oc == OpCodes.Bge_Un_S || oc == OpCodes.Bgt_Un || oc == OpCodes.Bge_Un_S || oc == OpCodes.Beq || oc == OpCodes.Beq_S || oc == OpCodes.Ble || oc == OpCodes.Ble_S || oc == OpCodes.Blt || oc == OpCodes.Blt_S;
        }
    }
}