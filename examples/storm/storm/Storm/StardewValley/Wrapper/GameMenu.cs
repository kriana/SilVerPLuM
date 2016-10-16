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
    public class GameMenu : ClickableMenu
    {
        public GameMenu(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public GameMenu()
        {
        }

        public int CurrentTab
        {
            get { return AsDynamic._GetCurrentTab(); }
            set { AsDynamic._SetCurrentTab(value); }
        }

        public string HoverText
        {
            get { return AsDynamic._GetHoverText(); }
            set { AsDynamic._SetHoverText(value); }
        }

        public string DescriptionText
        {
            get { return AsDynamic._GetDescriptionText(); }
            set { AsDynamic._SetDescriptionText(value); }
        }

        public bool Invisible
        {
            get { return AsDynamic._GetInvisible(); }
            set { AsDynamic._SetInvisible(value); }
        }

        public bool ForcePreventClose
        {
            get { return AsDynamic._GetForcePreventClose(); }
            set { AsDynamic._SetForcePreventClose(value); }
        }

        public WrappedProxyList<object, ClickableMenu> Pages
        {
            get
            {
                var tmp = AsDynamic._GetPages();
                if (tmp == null) return null;
                return new WrappedProxyList<object, ClickableMenu>((IList) tmp, i => i == null ? null : new ClickableMenu(Parent, i));
            }
        }
    }
}