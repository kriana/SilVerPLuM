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
using Microsoft.Xna.Framework.Audio;

namespace Storm.StardewValley.Wrapper
{
    public class FishingRod : Tool
    {
        public FishingRod(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public FishingRod()
        {
        }

        public Vector2 Bobber
        {
            get { return AsDynamic._GetBobber(); }
            set { AsDynamic._SetBobber(value); }
        }

        public int MinFishingBiteTime
        {
            get { return AsDynamic._GetMinFishingBiteTime(); }
            set { AsDynamic._SetMinFishingBiteTime(value); }
        }

        public int MaxFishingBiteTime
        {
            get { return AsDynamic._GetMaxFishingBiteTime(); }
            set { AsDynamic._SetMaxFishingBiteTime(value); }
        }

        public int MinTimeToNibble
        {
            get { return AsDynamic._GetMinTimeToNibble(); }
            set { AsDynamic._SetMinTimeToNibble(value); }
        }

        public int MaxTimeToNibble
        {
            get { return AsDynamic._GetMaxTimeToNibble(); }
            set { AsDynamic._SetMaxTimeToNibble(value); }
        }

        public double BaseChanceForTreasure
        {
            get { return AsDynamic._GetBaseChanceForTreasure(); }
            set { AsDynamic._SetBaseChanceForTreasure(value); }
        }

        public int BobberBob
        {
            get { return AsDynamic._GetBobberBob(); }
            set { AsDynamic._SetBobberBob(value); }
        }

        public float BobberTimeAccumulator
        {
            get { return AsDynamic._GetBobberTimeAccumulator(); }
            set { AsDynamic._SetBobberTimeAccumulator(value); }
        }

        public float TimePerBobberBob
        {
            get { return AsDynamic._GetTimePerBobberBob(); }
            set { AsDynamic._SetTimePerBobberBob(value); }
        }

        public float TimeUntilFishingBite
        {
            get { return AsDynamic._GetTimeUntilFishingBite(); }
            set { AsDynamic._SetTimeUntilFishingBite(value); }
        }

        public float FishingBiteAccumulator
        {
            get { return AsDynamic._GetFishingBiteAccumulator(); }
            set { AsDynamic._SetFishingBiteAccumulator(value); }
        }

        public float FishingNibbleAccumulator
        {
            get { return AsDynamic._GetFishingNibbleAccumulator(); }
            set { AsDynamic._SetFishingNibbleAccumulator(value); }
        }

        public float TimeUntilFishingNibbleDone
        {
            get { return AsDynamic._GetTimeUntilFishingNibbleDone(); }
            set { AsDynamic._SetTimeUntilFishingNibbleDone(value); }
        }

        public float CastingPower
        {
            get { return AsDynamic._GetCastingPower(); }
            set { AsDynamic._SetCastingPower(value); }
        }

        public float CastingChosenCountdown
        {
            get { return AsDynamic._GetCastingChosenCountdown(); }
            set { AsDynamic._SetCastingChosenCountdown(value); }
        }

        public float CastingTimerSpeed
        {
            get { return AsDynamic._GetCastingTimerSpeed(); }
            set { AsDynamic._SetCastingTimerSpeed(value); }
        }

        public float FishWiggle
        {
            get { return AsDynamic._GetFishWiggle(); }
            set { AsDynamic._SetFishWiggle(value); }
        }

        public float FishWiggleIntensity
        {
            get { return AsDynamic._GetFishWiggleIntensity(); }
            set { AsDynamic._SetFishWiggleIntensity(value); }
        }

        public bool IsFishing
        {
            get { return AsDynamic._GetIsFishing(); }
            set { AsDynamic._SetIsFishing(value); }
        }

        public bool Hit
        {
            get { return AsDynamic._GetHit(); }
            set { AsDynamic._SetHit(value); }
        }

        public bool IsNibbling
        {
            get { return AsDynamic._GetIsNibbling(); }
            set { AsDynamic._SetIsNibbling(value); }
        }

        public bool FavBait
        {
            get { return AsDynamic._GetFavBait(); }
            set { AsDynamic._SetFavBait(value); }
        }

        public bool IsTimingCast
        {
            get { return AsDynamic._GetIsTimingCast(); }
            set { AsDynamic._SetIsTimingCast(value); }
        }

        public bool IsCasting
        {
            get { return AsDynamic._GetIsCasting(); }
            set { AsDynamic._SetIsCasting(value); }
        }

        public bool CastedButBobberStillInAir
        {
            get { return AsDynamic._GetCastedButBobberStillInAir(); }
            set { AsDynamic._SetCastedButBobberStillInAir(value); }
        }

        public bool DoneWithAnimation
        {
            get { return AsDynamic._GetDoneWithAnimation(); }
            set { AsDynamic._SetDoneWithAnimation(value); }
        }

        public bool HasDoneFucntionYet
        {
            get { return AsDynamic._GetHasDoneFucntionYet(); }
            set { AsDynamic._SetHasDoneFucntionYet(value); }
        }

        public bool PullingOutOfWater
        {
            get { return AsDynamic._GetPullingOutOfWater(); }
            set { AsDynamic._SetPullingOutOfWater(value); }
        }

        public bool IsReeling
        {
            get { return AsDynamic._GetIsReeling(); }
            set { AsDynamic._SetIsReeling(value); }
        }

        public bool FishCaught
        {
            get { return AsDynamic._GetFishCaught(); }
            set { AsDynamic._SetFishCaught(value); }
        }

        public bool RecordSize
        {
            get { return AsDynamic._GetRecordSize(); }
            set { AsDynamic._SetRecordSize(value); }
        }

        public bool TreasureCaught
        {
            get { return AsDynamic._GetTreasureCaught(); }
            set { AsDynamic._SetTreasureCaught(value); }
        }

        public bool ShowingTreasure
        {
            get { return AsDynamic._GetShowingTreasure(); }
            set { AsDynamic._SetShowingTreasure(value); }
        }

        public bool HadBobber
        {
            get { return AsDynamic._GetHadBobber(); }
            set { AsDynamic._SetHadBobber(value); }
        }

        public bool BossFish
        {
            get { return AsDynamic._GetBossFish(); }
            set { AsDynamic._SetBossFish(value); }
        }

        public IList Animations
        {
            get { return AsDynamic._GetAnimations(); }
            set { AsDynamic._SetAnimations(value); }
        }

        public int FishSize
        {
            get { return AsDynamic._GetFishSize(); }
            set { AsDynamic._SetFishSize(value); }
        }

        public int WhichFish
        {
            get { return AsDynamic._GetWhichFish(); }
            set { AsDynamic._SetWhichFish(value); }
        }

        public int FishQuality
        {
            get { return AsDynamic._GetFishQuality(); }
            set { AsDynamic._SetFishQuality(value); }
        }

        public int ClearWaterDistance
        {
            get { return AsDynamic._GetClearWaterDistance(); }
            set { AsDynamic._SetClearWaterDistance(value); }
        }

        public int OriginalFacingDirection
        {
            get { return AsDynamic._GetOriginalFacingDirection(); }
            set { AsDynamic._SetOriginalFacingDirection(value); }
        }

        public Cue ChargeSound
        {
            get { return AsDynamic._GetChargeSound(); }
            set { AsDynamic._SetChargeSound(value); }
        }

        public Cue ReelSound
        {
            get { return AsDynamic._GetReelSound(); }
            set { AsDynamic._SetReelSound(value); }
        }

        public bool UsedGamePadToCast
        {
            get { return AsDynamic._GetUsedGamePadToCast(); }
            set { AsDynamic._SetUsedGamePadToCast(value); }
        }
    }
}