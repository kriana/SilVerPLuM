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
using Microsoft.Xna.Framework.Audio;

namespace Storm.StardewValley.Wrapper
{
    public class BobberBar : ClickableMenu
    {
        public BobberBar(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public BobberBar()
        {
        }

        public float Difficulty
        {
            get { return AsDynamic._GetDifficulty(); }
            set { AsDynamic._SetDifficulty(value); }
        }

        public int MotionType
        {
            get { return AsDynamic._GetMotionType(); }
            set { AsDynamic._SetMotionType(value); }
        }

        public int WhichFish
        {
            get { return AsDynamic._GetWhichFish(); }
            set { AsDynamic._SetWhichFish(value); }
        }

        public float BobberPosition
        {
            get { return AsDynamic._GetBobberPosition(); }
            set { AsDynamic._SetBobberPosition(value); }
        }

        public float BobberSpeed
        {
            get { return AsDynamic._GetBobberSpeed(); }
            set { AsDynamic._SetBobberSpeed(value); }
        }

        public float BobberAcceleration
        {
            get { return AsDynamic._GetBobberAcceleration(); }
            set { AsDynamic._SetBobberAcceleration(value); }
        }

        public float BobberTargetPosition
        {
            get { return AsDynamic._GetBobberTargetPosition(); }
            set { AsDynamic._SetBobberTargetPosition(value); }
        }

        public float Scale
        {
            get { return AsDynamic._GetScale(); }
            set { AsDynamic._SetScale(value); }
        }

        public float EverythingShakeTimer
        {
            get { return AsDynamic._GetEverythingShakeTimer(); }
            set { AsDynamic._SetEverythingShakeTimer(value); }
        }

        public float FloaterSinkerAcceleration
        {
            get { return AsDynamic._GetFloaterSinkerAcceleration(); }
            set { AsDynamic._SetFloaterSinkerAcceleration(value); }
        }

        public float TreasurePosition
        {
            get { return AsDynamic._GetTreasurePosition(); }
            set { AsDynamic._SetTreasurePosition(value); }
        }

        public float TreasureCatchLevel
        {
            get { return AsDynamic._GetTreasureCatchLevel(); }
            set { AsDynamic._SetTreasureCatchLevel(value); }
        }

        public float TreasureAppearTimer
        {
            get { return AsDynamic._GetTreasureAppearTimer(); }
            set { AsDynamic._SetTreasureAppearTimer(value); }
        }

        public float TreasureScale
        {
            get { return AsDynamic._GetTreasureScale(); }
            set { AsDynamic._SetTreasureScale(value); }
        }

        public bool BobberInBar
        {
            get { return AsDynamic._GetBobberInBar(); }
            set { AsDynamic._SetBobberInBar(value); }
        }

        public bool ButtonPressed
        {
            get { return AsDynamic._GetButtonPressed(); }
            set { AsDynamic._SetButtonPressed(value); }
        }

        public bool FlipBubble
        {
            get { return AsDynamic._GetFlipBubble(); }
            set { AsDynamic._SetFlipBubble(value); }
        }

        public bool FadeIn
        {
            get { return AsDynamic._GetFadeIn(); }
            set { AsDynamic._SetFadeIn(value); }
        }

        public bool FadeOut
        {
            get { return AsDynamic._GetFadeOut(); }
            set { AsDynamic._SetFadeOut(value); }
        }

        public bool Treasure
        {
            get { return AsDynamic._GetTreasure(); }
            set { AsDynamic._SetTreasure(value); }
        }

        public bool TreasureCaught
        {
            get { return AsDynamic._GetTreasureCaught(); }
            set { AsDynamic._SetTreasureCaught(value); }
        }

        public bool Perfect
        {
            get { return AsDynamic._GetPerfect(); }
            set { AsDynamic._SetPerfect(value); }
        }

        public bool BossFish
        {
            get { return AsDynamic._GetBossFish(); }
            set { AsDynamic._SetBossFish(value); }
        }

        public int BobberBarHeight
        {
            get { return AsDynamic._GetBobberBarHeight(); }
            set { AsDynamic._SetBobberBarHeight(value); }
        }

        public int FishSize
        {
            get { return AsDynamic._GetFishSize(); }
            set { AsDynamic._SetFishSize(value); }
        }

        public int FishQuality
        {
            get { return AsDynamic._GetFishQuality(); }
            set { AsDynamic._SetFishQuality(value); }
        }

        public int MinFishSize
        {
            get { return AsDynamic._GetMinFishSize(); }
            set { AsDynamic._SetMinFishSize(value); }
        }

        public int MaxFishSize
        {
            get { return AsDynamic._GetMaxFishSize(); }
            set { AsDynamic._SetMaxFishSize(value); }
        }

        public int FishSizeReductionTimer
        {
            get { return AsDynamic._GetFishSizeReductionTimer(); }
            set { AsDynamic._SetFishSizeReductionTimer(value); }
        }

        public int WhichBobber
        {
            get { return AsDynamic._GetWhichBobber(); }
            set { AsDynamic._SetWhichBobber(value); }
        }

        public Vector2 BarShake
        {
            get { return AsDynamic._GetBarShake(); }
            set { AsDynamic._SetBarShake(value); }
        }

        public Vector2 FishShake
        {
            get { return AsDynamic._GetFishShake(); }
            set { AsDynamic._SetFishShake(value); }
        }

        public Vector2 EverythingShake
        {
            get { return AsDynamic._GetEverythingShake(); }
            set { AsDynamic._SetEverythingShake(value); }
        }

        public Vector2 TreasureShake
        {
            get { return AsDynamic._GetTreasureShake(); }
            set { AsDynamic._SetTreasureShake(value); }
        }

        public float ReelRotation
        {
            get { return AsDynamic._GetReelRotation(); }
            set { AsDynamic._SetReelRotation(value); }
        }

        public float BobberBarPos
        {
            get { return AsDynamic._GetBobberBarPos(); }
            set { AsDynamic._SetBobberBarPos(value); }
        }

        public float BobberBarSpeed
        {
            get { return AsDynamic._GetBobberBarSpeed(); }
            set { AsDynamic._SetBobberBarSpeed(value); }
        }

        public float BobberBarAcceleration
        {
            get { return AsDynamic._GetBobberBarAcceleration(); }
            set { AsDynamic._SetBobberBarAcceleration(value); }
        }

        public float DistanceFromCatching
        {
            get { return AsDynamic._GetDistanceFromCatching(); }
            set { AsDynamic._SetDistanceFromCatching(value); }
        }

        public Cue ReelSound
        {
            get { return AsDynamic._GetReelSound(); }
            set { AsDynamic._SetReelSound(value); }
        }

        public Cue UnReelSound
        {
            get { return AsDynamic._GetUnReelSound(); }
            set { AsDynamic._SetUnReelSound(value); }
        }
    }
}