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
using Microsoft.Xna.Framework.Graphics;

namespace Storm.StardewValley.Wrapper
{
    public class HoeDirt : TerrainFeature
    {
        public HoeDirt(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public HoeDirt()
        {
        }

        public Texture2D LightTexture
        {
            get { return AsDynamic._GetLightTexture(); }
            set { AsDynamic._SetLightTexture(value); }
        }

        public Texture2D DarkTexture
        {
            get { return AsDynamic._GetDarkTexture(); }
            set { AsDynamic._SetDarkTexture(value); }
        }

        public Texture2D SnowTexture
        {
            get { return AsDynamic._GetSnowTexture(); }
            set { AsDynamic._SetSnowTexture(value); }
        }

        public Crop Crop
        {
            get
            {
                var tmp = AsDynamic._GetCrop();
                if (tmp == null) return null;
                return new Crop(Parent, tmp);
            }
            set { AsDynamic._SetCrop(value?.Underlying); }
        }

        public int State
        {
            get { return AsDynamic._GetState(); }
            set { AsDynamic._SetState(value); }
        }

        public int Fertilizer
        {
            get { return AsDynamic._GetFertilizer(); }
            set { AsDynamic._SetFertilizer(value); }
        }

        public bool ShakeLeft
        {
            get { return AsDynamic._GetShakeLeft(); }
            set { AsDynamic._SetShakeLeft(value); }
        }

        public float ShakeRotation
        {
            get { return AsDynamic._GetShakeRotation(); }
            set { AsDynamic._SetShakeRotation(value); }
        }

        public float MaxShake
        {
            get { return AsDynamic._GetMaxShake(); }
            set { AsDynamic._SetMaxShake(value); }
        }

        public float ShakeRate
        {
            get { return AsDynamic._GetShakeRate(); }
            set { AsDynamic._SetShakeRate(value); }
        }

        public Color C
        {
            get { return AsDynamic._GetC(); }
            set { AsDynamic._SetC(value); }
        }

        public bool IsReadyForHarvest => AsDynamic._IsReadyForHarvest();
    }
}