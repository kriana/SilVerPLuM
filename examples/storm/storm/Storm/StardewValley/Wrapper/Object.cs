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
    public class ObjectItem : Item
    {
        public ObjectItem(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public ObjectItem()
        {
        }

        public int SellToStorePrice => AsDynamic._GetSellToStorePrice();

        public Vector2 TileLocation
        {
            get { return AsDynamic._GetTileLocation(); }
            set { AsDynamic._SetTileLocation(value); }
        }

        public bool CanBeGrabbed
        {
            get { return AsDynamic._GetCanBeGrabbed(); }
            set { AsDynamic._SetCanBeGrabbed(value); }
        }

        public bool CanBeSetDown
        {
            get { return AsDynamic._GetCanBeSetDown(); }
            set { AsDynamic._SetCanBeSetDown(value); }
        }

        public int Edibility
        {
            get { return AsDynamic._GetEdibility(); }
            set { AsDynamic._SetEdibility(value); }
        }

        public bool Flipped
        {
            get { return AsDynamic._GetFlipped(); }
            set { AsDynamic._SetFlipped(value); }
        }

        public int Fragility
        {
            get { return AsDynamic._GetFragility(); }
            set { AsDynamic._SetFragility(value); }
        }

        public bool HasBeenPickedUpByFarmer
        {
            get { return AsDynamic._GetHasBeenPickedUpByFarmer(); }
            set { AsDynamic._SetHasBeenPickedUpByFarmer(value); }
        }

        public bool IsActive
        {
            get { return AsDynamic._GetIsActive(); }
            set { AsDynamic._SetIsActive(value); }
        }

        public bool IsHoeDirt
        {
            get { return AsDynamic._GetIsHoedirt(); }
            set { AsDynamic._SetIsHoedirt(value); }
        }

        public bool IsLamp
        {
            get { return AsDynamic._GetIsLamp(); }
            set { AsDynamic._SetIsLamp(true); }
        }

        public bool IsOn
        {
            get { return AsDynamic._GetIsOn(); }
            set { AsDynamic._SetIsOn(value); }
        }

        public bool IsRecipe
        {
            get { return AsDynamic._GetIsRecipe(); }
            set { AsDynamic._SetIsRecipe(value); }
        }

        public bool IsSpawned
        {
            get { return AsDynamic._GetIsSpawnedObject(); }
            set { AsDynamic._SetIsSpawnedObject(value); }
        }

        public string Name
        {
            get { return AsDynamic._GetName(); }
            set { AsDynamic._SetName(value); }
        }

        public long Owner
        {
            get { return AsDynamic._GetOwner(); }
            set { AsDynamic._SetOwner(value); }
        }

        public int Price
        {
            get { return AsDynamic._GetPrice(); }
            set { AsDynamic._SetPrice(value); }
        }

        public int Quality
        {
            get { return AsDynamic._GetQuality(); }
            set { AsDynamic._SetQuality(value); }
        }

        public int Stack
        {
            get { return AsDynamic._GetStack(); }
            set { AsDynamic._SetStack(value); }
        }


        public bool IsQuestItem
        {
            get { return AsDynamic._GetQuestItem(); }
            set { AsDynamic._SetQuestItem(value); }
        }

        public bool ReadyForHarvest
        {
            get { return AsDynamic._GetReadyForHarvest(); }
            set { AsDynamic._SetReadyForHarvest(value); }
        }

        public Vector2 Scale
        {
            get { return AsDynamic._GetScale(); }
            set { AsDynamic._SetScale(value); }
        }

        public string Type
        {
            get { return AsDynamic._GetType(); }
            set { AsDynamic._SetType(value); }
        }

        public ObjectItem HeldObject
        {
            get
            {
                var tmp = AsDynamic._GetHeldObject();
                if (tmp == null) return null;
                return new ObjectItem(Parent, tmp);
            }
            set { AsDynamic._SetHeldObject(value?.Underlying); }
        }

        public int MinutesUntilReady
        {
            get { return AsDynamic._GetMinutesUntilReady(); }
            set { AsDynamic._SetMinutesUntilReady(value); }
        }

        public Rectangle BoundingBox
        {
            get { return AsDynamic._GetBoundingBox(); }
            set { AsDynamic._SetBoundingBox(value); }
        }
    }
}