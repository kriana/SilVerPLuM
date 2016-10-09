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

using Microsoft.Xna.Framework;

namespace Storm.StardewValley.Wrapper
{
    public class Character : StaticContextWrapper
    {
        public Character(StaticContext parent, object accessor) : base(parent)
        {
            Underlying = accessor;
        }

        public Character()
        {
        }

        public bool EmoteFading => AsDynamic._GetEmoteFading();

        public float EmoteInterval
        {
            get { return AsDynamic._GetEmoteInterval(); }
            set { AsDynamic._SetEmoteInterval(value); }
        }

        public Vector2 LastClick
        {
            get { return AsDynamic._GetLastClick(); }
            set { AsDynamic._SetLastClick(value); }
        }

        public string Name
        {
            get { return AsDynamic._GetName(); }
            set { AsDynamic._SetName(value); }
        }

        public Vector2 Position
        {
            get { return AsDynamic._GetPosition(); }
            set { AsDynamic._SetPosition(value); }
        }

        public float VelocityX
        {
            get { return AsDynamic._GetXVelocity(); }
            set { AsDynamic._SetXVelocity(value); }
        }

        public float VelocityY
        {
            get { return AsDynamic._GetYVelocity(); }
            set { AsDynamic._SetYVelocity(value); }
        }

        public float Scale
        {
            get { return AsDynamic._GetScale(); }
            set { AsDynamic._SetScale(value); }
        }

        public int Speed
        {
            get { return AsDynamic._GetSpeed(); }
            set { AsDynamic._SetSpeed(value); }
        }

        public AnimatedSprite Sprite
        {
            get
            {
                var tmp = AsDynamic._GetSprite();
                if (tmp == null) return null;
                return new AnimatedSprite(Parent, tmp);
            }
            set { AsDynamic._SetSprite(value?.Underlying); }
        }
    }
}