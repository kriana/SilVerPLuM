/*
    Copyright 2016 Cody R. (Demmonic), Inari-Whitebear

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

using Microsoft.Xna.Framework.Graphics;

namespace Storm.StardewValley.Wrapper
{
    public class Fence : ObjectItem
    {
        public Fence(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public Fence()
        {
        }

        public int FencePieceWidth
        {
            get { return AsDynamic._GetFencePieceWidth(); }
            set { AsDynamic._SetFencePieceWidth(value); }
        }

        public int FencePieceHeight
        {
            get { return AsDynamic._GetFencePieceHeight(); }
            set { AsDynamic._SetFencePieceHeight(value); }
        }

        public Texture2D FenceTexture
        {
            get { return AsDynamic._GetFenceTexture(); }
            set { AsDynamic._SetFenceTexture(value); }
        }

        public float Health
        {
            get { return AsDynamic._GetHealth(); }
            set { AsDynamic._SetHealth(value); }
        }

        public float MaxHealth
        {
            get { return AsDynamic._GetMaxHealth(); }
            set { AsDynamic._SetMaxHealth(value); }
        }

        public int WhichType
        {
            get { return AsDynamic._GetWhichType(); }
            set { AsDynamic._SetWhichType(value); }
        }

        public int GatePosition
        {
            get { return AsDynamic._GetGatePosition(); }
            set { AsDynamic._SetGatePosition(value); }
        }

        public int GateMotion
        {
            get { return AsDynamic._GetGateMotion(); }
            set { AsDynamic._SetGateMotion(value); }
        }

        public bool IsGate
        {
            get { return AsDynamic._GetIsGate(); }
            set { AsDynamic._SetIsGate(value); }
        }
    }
}