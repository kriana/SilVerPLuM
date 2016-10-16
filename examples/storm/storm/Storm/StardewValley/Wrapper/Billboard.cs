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
using Microsoft.Xna.Framework.Graphics;
using Storm.Collections;

namespace Storm.StardewValley.Wrapper
{
    public class Billboard : ClickableMenu
    {
        public Billboard(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public Billboard()
        {
        }

        public Texture2D BillboardTexture
        {
            get { return AsDynamic._GetBillboardTexture(); }
            set { AsDynamic._SetBillboardTexture(value); }
        }

        public bool DailyQuestBoard
        {
            get { return AsDynamic._GetDailyQuestBoard(); }
            set { AsDynamic._SetDailyQuestBoard(value); }
        }

        public ClickableComponent AcceptQuestButton
        {
            get
            {
                var tmp = AsDynamic._GetAcceptQuestButton();
                if (tmp == null) return null;
                return new ClickableComponent(Parent, tmp);
            }
            set { AsDynamic._SetAcceptQuestButton(value.Underlying); }
        }

        public WrappedProxyList<object, ClickableTextureComponent> CalendarDays
        {
            get
            {
                var tmp = AsDynamic._GetCalendarDays();
                if (tmp == null) return null;
                return new WrappedProxyList<object, ClickableTextureComponent>((IList) tmp, i => new ClickableTextureComponent(Parent, i));
            }
        }

        public string HoverText
        {
            get { return AsDynamic._GetHoverText(); }
            set { AsDynamic._SetHoverText(value); }
        }
    }
}