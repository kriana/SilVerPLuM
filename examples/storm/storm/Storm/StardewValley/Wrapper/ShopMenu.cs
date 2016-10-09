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
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Storm.Collections;

namespace Storm.StardewValley.Wrapper
{
    public class ShopMenu : ClickableMenu
    {
        public ShopMenu(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public ShopMenu()
        {
        }

        public WrappedProxyList<object, Item> ItemsForSale
        {
            get
            {
                var tmp = AsDynamic._GetForSale();
                if (tmp == null) return null;
                return new WrappedProxyList<object, Item>((IList) tmp, i => new Item(Parent, i));
            }
        }

        public KeyProxyDictionary<Item, int[]> ItemsForSaleData
        {
            get
            {
                var tmp = AsDynamic._GetItemPriceAndStock();
                if (tmp == null) return null;
                return new KeyProxyDictionary<Item, int[]>(tmp);
            }
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

        public string BoldTitleText
        {
            get { return AsDynamic._GetBoldTitleText(); }
            set { AsDynamic._SetBoldTitleText(value); }
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

        public Texture2D Wallpapers
        {
            get { return AsDynamic._GetWallpapers(); }
            set { AsDynamic._SetWallpapers(value); }
        }

        public Texture2D Floors
        {
            get { return AsDynamic._GetFloors(); }
            set { AsDynamic._SetFloors(value); }
        }

        public int LastWallpaperFloorPrice
        {
            get { return AsDynamic._GetLastWallpaperFloorPrice(); }
            set { AsDynamic._SetLastWallpaperFloorPrice(value); }
        }

        public Rectangle ScrollBarRunner
        {
            get { return AsDynamic._GetScrollBarRunner(); }
            set { AsDynamic._SetScrollBarRunner(value); }
        }

        public float SellPercentage
        {
            get { return AsDynamic._GetSellPercentage(); }
            set { AsDynamic._SetSellPercentage(value); }
        }

        public IList Animations
        {
            get { return AsDynamic._GetAnimations(); }
            set { AsDynamic._SetAnimations(value); }
        }

        public int HoverPrice
        {
            get { return AsDynamic._GetHoverPrice(); }
            set { AsDynamic._SetHoverPrice(value); }
        }

        public int Currency
        {
            get { return AsDynamic._GetCurrency(); }
            set { AsDynamic._SetCurrency(value); }
        }

        public int CurrentItemIndex
        {
            get { return AsDynamic._GetCurrentItemIndex(); }
            set { AsDynamic._SetCurrentItemIndex(value); }
        }

        public ClickableTextureComponent UpArrow
        {
            get
            {
                var tmp = AsDynamic._GetUpArrow();
                if (tmp == null) return null;
                return new ClickableTextureComponent(Parent, tmp);
            }
            set { AsDynamic._SetUpArrow(value?.Underlying); }
        }

        public ClickableTextureComponent DownArrow
        {
            get
            {
                var tmp = AsDynamic._GetDownArrow();
                if (tmp == null) return null;
                return new ClickableTextureComponent(Parent, tmp);
            }
            set { AsDynamic._SetDownArrow(value?.Underlying); }
        }

        public ClickableTextureComponent ScrollBar
        {
            get
            {
                var tmp = AsDynamic._GetScrollBar();
                if (tmp == null) return null;
                return new ClickableTextureComponent(Parent, tmp);
            }
            set { AsDynamic._SetScrollBar(value?.Underlying); }
        }

        public Npc PortraitPerson
        {
            get
            {
                var tmp = AsDynamic._GetPortraitPerson();
                if (tmp == null) return null;
                return new Npc(Parent, tmp);
            }
            set { AsDynamic._SetPortraitPerson(value?.Underlying); }
        }

        public string PotraitPersonDialogue
        {
            get { return AsDynamic._GetPotraitPersonDialogue(); }
            set { AsDynamic._SetPotraitPersonDialogue(value); }
        }

        public bool Scrolling
        {
            get { return AsDynamic._GetScrolling(); }
            set { AsDynamic._SetScrolling(value); }
        }

        public bool AddForSale(Item item, int price, int amount = int.MaxValue)
        {
            var list = ItemsForSale;
            if (list == null) return false;
            var dict = ItemsForSaleData;
            if (dict == null) return false;
            list.Add(item);
            dict.Add(item, new[] {price, amount});
            return true;
        }
    }
}