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
using Storm.Collections;

namespace Storm.StardewValley.Wrapper
{
    public class Chest : ObjectItem
    {
        public Chest(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public Chest()
        {
        }

        public WrappedProxyList<object, Item> Items
        {
            get
            {
                var tmp = AsDynamic._GetItems();
                if (tmp == null) return null;
                return new WrappedProxyList<object, Item>((IList) tmp, i => new Item(Parent, i));
            }
        }

        public int CurrentLidFrame
        {
            get { return AsDynamic._GetCurrentLidFrame(); }
            set { AsDynamic._SetCurrentLidFrame(value); }
        }

        public int FrameCounter
        {
            get { return AsDynamic._GetFrameCounter(); }
            set { AsDynamic._SetFrameCounter(value); }
        }

        public int Coins
        {
            get { return AsDynamic._GetCoins(); }
            set { AsDynamic._SetCoins(value); }
        }

        public Farmer Opener
        {
            get
            {
                var tmp = AsDynamic._GetOpener();
                if (tmp == null) return null;
                return new Farmer(Parent, tmp);
            }
            set { AsDynamic._SetOpener(value?.Underlying); }
        }

        public string ChestType
        {
            get { return AsDynamic._GetChestType(); }
            set { AsDynamic._SetChestType(value); }
        }

        public Color Tint
        {
            get { return AsDynamic._GetTint(); }
            set { AsDynamic._SetTint(value); }
        }

        public bool PlayerChest
        {
            get { return AsDynamic._GetPlayerChest(); }
            set { AsDynamic._SetPlayerChest(value); }
        }

        public bool Giftbox
        {
            get { return AsDynamic._GetGiftbox(); }
            set { AsDynamic._SetGiftbox(value); }
        }
    }
}