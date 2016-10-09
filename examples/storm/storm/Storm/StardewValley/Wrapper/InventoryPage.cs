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
    public class InventoryPage : ClickableMenu
    {
        public InventoryPage(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public InventoryPage()
        {
        }

        public InventoryMenu Inventory
        {
            get
            {
                var tmp = AsDynamic._GetInventory();
                if (tmp == null) return null;
                return new InventoryMenu(Parent, tmp);
            }
            set { AsDynamic._SetInventory(value?.Underlying); }
        }

        public string DescriptionText
        {
            get { return AsDynamic._GetDescriptionText(); }
            set { AsDynamic._SetDescriptionText(value); }
        }

        public string HoverText
        {
            get { return AsDynamic._GetHoverText(); }
            set { AsDynamic._SetHoverText(value); }
        }

        public string DescriptionTitle
        {
            get { return AsDynamic._GetDescriptionTitle(); }
            set { AsDynamic._SetDescriptionTitle(value); }
        }

        public string HoverTitle
        {
            get { return AsDynamic._GetHoverTitle(); }
            set { AsDynamic._SetHoverTitle(value); }
        }

        public Item HeldItem
        {
            get
            {
                var tmp = AsDynamic._GetHeldItem();
                if (tmp == null) return null;
                return new Item(Parent, tmp);
            }
            set { AsDynamic._SetHeldItem(value?.Underlying); }
        }

        public Item HoveredItem
        {
            get
            {
                var tmp = AsDynamic._GetHoveredItem();
                if (tmp == null) return null;
                return new Item(Parent, tmp);
            }
            set { AsDynamic._SetHoveredItem(value?.Underlying); }
        }

        public float TrashCanLidRotation
        {
            get { return AsDynamic._GetTrashCanLidRotation(); }
            set { AsDynamic._SetTrashCanLidRotation(value); }
        }

        public string HorseName
        {
            get { return AsDynamic._GetHorseName(); }
            set { AsDynamic._SetHorseName(value); }
        }
    }
}