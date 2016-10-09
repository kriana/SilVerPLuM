/*
    Copyright 2016

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
    public class FarmAnimal : Character
    {
        public FarmAnimal(StaticContext parent, object accessor) :
            base(parent, accessor)
        {
        }

        public FarmAnimal()
        {
        }

        public int DefaultProduceIndex
        {
            get { return AsDynamic._GetDefaultProduceIndex(); }
            set { AsDynamic._SetDefaultProduceIndex(value); }
        }

        public int DeluxeProduceIndex
        {
            get { return AsDynamic._GetDeluxeProduceIndex(); }
            set { AsDynamic._SetDeluxeProduceIndex(value); }
        }

        public int CurrentProduce
        {
            get { return AsDynamic._GetCurrentProduce(); }
            set { AsDynamic._SetCurrentProduce(value); }
        }

        public int FriendshipTowardsFarmer
        {
            get { return AsDynamic._GetFriendshipTowardFarmer(); }
            set { AsDynamic._SetFriendshipTowardFarmer(value); }
        }

        public int DaysSinceLastFed
        {
            get { return AsDynamic._GetDaysSinceLastFed(); }
            set { AsDynamic._SetDaysSinceLastFed(value); }
        }

        public int PushAccumulator
        {
            get { return AsDynamic._GetPushAccumulator(); }
            set { AsDynamic._SetPushAccumulator(value); }
        }

        public int UniqueFrameAccumulator
        {
            get { return AsDynamic._GetUniqueFrameAccumulator(); }
            set { AsDynamic._SetUniqueFrameAccumulator(value); }
        }

        public int Age
        {
            get { return AsDynamic._GetAge(); }
            set { AsDynamic._SetAge(value); }
        }

        public int MeatIndex
        {
            get { return AsDynamic._GetMeatIndex(); }
            set { AsDynamic._SetMeatIndex(value); }
        }

        public int Health
        {
            get { return AsDynamic._GetHealth(); }
            set { AsDynamic._SetHealth(value); }
        }

        public int Price
        {
            get { return AsDynamic._GetPrice(); }
            set { AsDynamic._SetPrice(value); }
        }

        public int ProduceQuality
        {
            get { return AsDynamic._GetProduceQuality(); }
            set { AsDynamic._SetProduceQuality(value); }
        }

        public byte DaysToLay
        {
            get { return AsDynamic._GetDaysToLay(); }
            set { AsDynamic._SetDaysToLay(value); }
        }

        public byte DaysSinceLastLay
        {
            get { return AsDynamic._GetDaysSinceLastLay(); }
            set { AsDynamic._SetDaysSinceLastLay(value); }
        }

        public byte AgeWhenMature
        {
            get { return AsDynamic._GetAgeWhenMature(); }
            set { AsDynamic._SetAgeWhenMature(value); }
        }

        public byte HarvestType
        {
            get { return AsDynamic._GetHarvestType(); }
            set { AsDynamic._SetHarvestType(value); }
        }

        public byte Happiness
        {
            get { return AsDynamic._GetHappiness(); }
            set { AsDynamic._SetHappiness(value); }
        }

        public byte Fullness
        {
            get { return AsDynamic._GetFullness(); }
            set { AsDynamic._SetFullness(value); }
        }

        public byte HappinessDrain
        {
            get { return AsDynamic._GetHappinessDrain(); }
            set { AsDynamic._SetHappinessDrain(value); }
        }

        public byte FullnessDrain
        {
            get { return AsDynamic._GetFullnessDrain(); }
            set { AsDynamic._SetFullnessDrain(value); }
        }

        public bool WasPet
        {
            get { return AsDynamic._GetWasPet(); }
            set { AsDynamic._SetWasPet(value); }
        }

        public bool ShowDifferentTextureWhenReadyForHarvest
        {
            get { return AsDynamic._GetShowDifferentTextureWhenReadyForHarvest(); }
            set { AsDynamic._SetShowDifferentTextureWhenReadyForHarvest(value); }
        }

        public bool AllowReproduction
        {
            get { return AsDynamic._GetAllowReproduction(); }
            set { AsDynamic._SetAllowReproduction(value); }
        }

        public string Sound
        {
            get { return AsDynamic._GetSound(); }
            set { AsDynamic._SetSound(value); }
        }

        public string Type
        {
            get { return AsDynamic._GetType(); }
            set { AsDynamic._SetType(value); }
        }

        public string BuildingTypeILiveIn
        {
            get { return AsDynamic._GetBuildingTypeILiveIn(); }
            set { AsDynamic._SetBuildingTypeILiveIn(value); }
        }

        public string ToolUsedForHarvest
        {
            get { return AsDynamic._GetToolUsedForHarvest(); }
            set { AsDynamic._SetToolUsedForHarvest(value); }
        }

        public Rectangle FrontBackBoundingBox
        {
            get { return AsDynamic._GetFrontBackBoundingBox(); }
            set { AsDynamic._SetFrontBackBoundingBox(value); }
        }

        public Rectangle SidewaysBoundingBox
        {
            get { return AsDynamic._GetSidewaysBoundingBox(); }
            set { AsDynamic._SetSidewaysBoundingBox(value); }
        }

        public Rectangle FrontBackSourceRect
        {
            get { return AsDynamic._GetFrontBackSourceRect(); }
            set { AsDynamic._SetFrontBackSourceRect(value); }
        }

        public Rectangle SidewaysSourceRect
        {
            get { return AsDynamic._GetSidewaysSourceRect(); }
            set { AsDynamic._SetSidewaysSourceRect(value); }
        }

        public long MyId
        {
            get { return AsDynamic._GetMyID(); }
            set { AsDynamic._SetMyID(value); }
        }

        public long OwnerId
        {
            get { return AsDynamic._GetOwnerID(); }
            set { AsDynamic._SetOwnerID(value); }
        }

        public long ParentId
        {
            get { return AsDynamic._GetParentId(); }
            set { AsDynamic._SetParentId(value); }
        }

        public Vector2 HomeLocation
        {
            get { return AsDynamic._GetHomeLocation(); }
            set { AsDynamic._SetHomeLocation(value); }
        }

        public int NoWarpTime
        {
            get { return AsDynamic._GetNoWarpTimer(); }
            set { AsDynamic._SetNoWarpTimer(value); }
        }

        public int HitGlowTimer
        {
            get { return AsDynamic._GetHitGlowTimer(); }
            set { AsDynamic._SetHitGlowTimer(value); }
        }

        public int PauseTimer
        {
            get { return AsDynamic._GetPauseTimer(); }
            set { AsDynamic._SetPauseTimer(value); }
        }

        public short MoodMessage
        {
            get { return AsDynamic._GetMoodMessage(); }
            set { AsDynamic._SetMoodMessage(value); }
        }

        public bool IsEating
        {
            get { return AsDynamic._GetIsEating(); }
            set { AsDynamic._SetIsEating(value); }
        }
    }
}