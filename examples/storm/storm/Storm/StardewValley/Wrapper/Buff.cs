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
    public class Buff : StaticContextWrapper
    {
        public Buff(StaticContext parent, object accessor) : base(parent)
        {
            Underlying = accessor;
        }

        public Buff()
        {
        }

        public int MillisecondsDuration
        {
            get { return AsDynamic._GetMillisecondsDuration(); }
            set { AsDynamic._SetMillisecondsDuration(value); }
        }

        public string Description
        {
            get { return AsDynamic._GetDescription(); }
            set { AsDynamic._SetDescription(value); }
        }

        public string Source
        {
            get { return AsDynamic._GetSource(); }
            set { AsDynamic._SetSource(value); }
        }

        public int Total
        {
            get { return AsDynamic._GetTotal(); }
            set { AsDynamic._SetTotal(value); }
        }

        public int SheetIndex
        {
            get { return AsDynamic._GetSheetIndex(); }
            set { AsDynamic._SetSheetIndex(value); }
        }

        public int Which
        {
            get { return AsDynamic._GetWhich(); }
            set { AsDynamic._SetWhich(value); }
        }

        public Color Glow
        {
            get { return AsDynamic._GetGlow(); }
            set { AsDynamic._SetGlow(value); }
        }
    }
}