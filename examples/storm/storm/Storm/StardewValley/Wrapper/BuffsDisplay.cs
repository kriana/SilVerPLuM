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

using System.Collections;
using Storm.Collections;

namespace Storm.StardewValley.Wrapper
{
    public class BuffsDisplay : ClickableMenu
    {
        public BuffsDisplay(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public BuffsDisplay()
        {
        }

        public Buff Food
        {
            get
            {
                var tmp = AsDynamic._GetFood();
                if (tmp == null) return null;
                return new Buff(Parent, tmp);
            }
            set { AsDynamic._SetFood(value?.Underlying); }
        }

        public Buff Drink
        {
            get
            {
                var tmp = AsDynamic._GetDrink();
                if (tmp == null) return null;
                return new Buff(Parent, tmp);
            }
            set { AsDynamic._SetDrink(value?.Underlying); }
        }

        public WrappedProxyList<object, Buff> OtherBuffs
        {
            get
            {
                var tmp = AsDynamic._GetOtherBuffs();
                if (tmp == null) return null;
                return new WrappedProxyList<object, Buff>((IList) tmp, i => new Buff(Parent, i));
            }
        }

        public int FullnessLeft
        {
            get { return AsDynamic._GetFullnessLeft(); }
            set { AsDynamic._SetFullnessLeft(value); }
        }

        public int QuenchedLeft
        {
            get { return AsDynamic._GetQuenchedLeft(); }
            set { AsDynamic._SetQuenchedLeft(value); }
        }

        public string HoverText
        {
            get { return AsDynamic._GetHoverText(); }
            set { AsDynamic._SetHoverText(value); }
        }

        public bool TryToAddFoodBuff(Buff buff, int duration)
        {
            return AsDynamic._TryToAddFoodBuff(buff?.Underlying, duration);
        }

        public bool TryToAddDrinkBuff(Buff buff)
        {
            return AsDynamic._TryToAddDrinkBuff(buff?.Underlying);
        }

        public bool AddOtherBuff(Buff buff)
        {
            return AsDynamic._AddOtherBuff(buff?.Underlying);
        }
    }
}