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

namespace Storm.StardewValley.Wrapper
{
    public class InventoryMenu : ClickableMenu
    {
        public InventoryMenu(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public InventoryMenu()
        {
        }

        public string HoverText
        {
            get { return AsDynamic._GetHoverText(); }
            set { AsDynamic._SetHoverText(value); }
        }

        public string HoverTitle
        {
            get { return AsDynamic._GetHoverTitle(); }
            set { AsDynamic._SetHoverTitle(value); }
        }

        public string DescriptionTitle
        {
            get { return AsDynamic._GetDescriptionTitle(); }
            set { AsDynamic._SetDescriptionTitle(value); }
        }

        public string DescriptionText
        {
            get { return AsDynamic._GetDescriptionText(); }
            set { AsDynamic._SetDescriptionText(value); }
        }

        public bool PlayerInventory
        {
            get { return AsDynamic._GetPlayerInventory(); }
            set { AsDynamic._SetPlayerInventory(value); }
        }

        public bool DrawSlots
        {
            get { return AsDynamic._GetDrawSlots(); }
            set { AsDynamic._SetDrawSlots(value); }
        }

        public bool ShowGrayedOutSlots
        {
            get { return AsDynamic._GetShowGrayedOutSlots(); }
            set { AsDynamic._SetShowGrayedOutSlots(value); }
        }

        public int Capacity
        {
            get { return AsDynamic._GetCapacity(); }
            set { AsDynamic._SetCapacity(value); }
        }

        public int Rows
        {
            get { return AsDynamic._GetRows(); }
            set { AsDynamic._SetRows(value); }
        }

        public int HorizontalGap
        {
            get { return AsDynamic._GetHorizontalGap(); }
            set { AsDynamic._SetHorizontalGap(value); }
        }

        public int VerticalGap
        {
            get { return AsDynamic._GetVerticalGap(); }
            set { AsDynamic._SetVerticalGap(value); }
        }

        public Item GetItemAt(int mouseX, int mouseY)
        {
            var tmp = AsDynamic._GetItemAt(mouseX, mouseY);
            if (tmp == null) return null;
            return new Item(Parent, tmp);
        }
    }
}