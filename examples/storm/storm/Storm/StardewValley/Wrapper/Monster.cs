/*
    Copyright 2016 Inari-Whitebear

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
    public class Monster : Npc
    {
        public Monster(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public Monster()
        {
        }

        public int DamageToFarmer
        {
            get { return AsDynamic._GetDamageToFarmer(); }
            set { AsDynamic._SetDamageToFarmer(value); }
        }

        public int Health
        {
            get { return AsDynamic._GetHealth(); }
            set { AsDynamic._SetHealth(value); }
        }

        public int MaxHealth
        {
            get { return AsDynamic._GetMaxHealth(); }
            set { AsDynamic._SetMaxHealth(value); }
        }

        public int CoinsToDrop
        {
            get { return AsDynamic._GetCoinsToDrop(); }
            set { AsDynamic._SetCoinsToDrop(value); }
        }

        public int DurationOfRandomMovements
        {
            get { return AsDynamic._GetDurationOfRandomMovements(); }
            set { AsDynamic._SetDurationOfRandomMovements(value); }
        }

        public int Resilience
        {
            get { return AsDynamic._GetResilience(); }
            set { AsDynamic._SetResilience(value); }
        }

        public int Slipperiness
        {
            get { return AsDynamic._GetSlipperiness(); }
            set { AsDynamic._SetSlipperiness(value); }
        }

        public int ExperienceGained
        {
            get { return AsDynamic._GetExperienceGained(); }
            set { AsDynamic._SetExperienceGained(value); }
        }

        public double Jitteriness
        {
            get { return AsDynamic._GetJitteriness(); }
            set { AsDynamic._SetJitteriness(value); }
        }

        public double MissChance
        {
            get { return AsDynamic._GetMissChance(); }
            set { AsDynamic._SetMissChance(value); }
        }

        public bool IsGlider
        {
            get { return AsDynamic._GetIsGlider(); }
            set { AsDynamic._SetIsGlider(value); }
        }

        public bool MineMonster
        {
            get { return AsDynamic._GetMineMonster(); }
            set { AsDynamic._SetMineMonster(value); }
        }

        public bool HasSpecialItem
        {
            get { return AsDynamic._GetHasSpecialItem(); }
            set { AsDynamic._SetHasSpecialItem(value); }
        }

        public int SkipHorizontal
        {
            get { return AsDynamic._GetSkipHorizontal(); }
            set { AsDynamic._SetSkipHorizontal(value); }
        }

        public int InvincibleCountdown
        {
            get { return AsDynamic._GetInvincibleCountdown(); }
            set { AsDynamic._SetInvincibleCountdown(value); }
        }

        public bool SkipHorizontalUp
        {
            get { return AsDynamic._GetSkipHorizontalUp(); }
            set { AsDynamic._SetSkipHorizontalUp(value); }
        }

        public int DefaultAnimationInterval
        {
            get { return AsDynamic._GetDefaultAnimationInterval(); }
            set { AsDynamic._SetDefaultAnimationInterval(value); }
        }

        public bool FocusedOnFarmers
        {
            get { return AsDynamic._GetFocusedOnFarmers(); }
            set { AsDynamic._SetFocusedOnFarmers(value); }
        }

        public int SlideAnimationTimer
        {
            get { return AsDynamic._GetSlideAnimationTimer(); }
            set { AsDynamic._SetSlideAnimationTimer(value); }
        }
    }
}