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
    public class Item : StaticContextWrapper
    {
        public Item(StaticContext parent, object accessor) : base(parent)
        {
            Underlying = accessor;
        }

        public Item()
        {
        }

        public int SalePrice => AsDynamic._GetSalePrice();

        public int MaximumStackSize => AsDynamic._GetMaximumStackSize();

        public string Description => AsDynamic._GetDescription();

        public int Category
        {
            get { return AsDynamic._GetCategory(); }
            set { AsDynamic._SetCategory(value); }
        }

        public bool HasBeenInInventory
        {
            get { return AsDynamic._GetHasBeenInInventory(); }
            set { AsDynamic._SetHasBeenInInventory(value); }
        }

        public bool IsSpecialItem
        {
            get { return AsDynamic._GetSpecialItem(); }
            set { AsDynamic._SetSpecialItem(value); }
        }

        public int SpecialVariable
        {
            get { return AsDynamic._GetSpecialVariable(); }
            set { AsDynamic._SetSpecialVariable(value); }
        }
    }
}