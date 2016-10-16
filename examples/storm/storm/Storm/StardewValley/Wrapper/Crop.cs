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

using Storm.Collections;

namespace Storm.StardewValley.Wrapper
{
    public class Crop : StaticContextWrapper
    {
        public Crop(StaticContext parent, object accessor) : base(parent)
        {
            Underlying = accessor;
        }

        public Crop()
        {
        }

        /// <summary>
        ///     The chance for this crop to drop extra products
        /// </summary>
        /// <value>The ChanceForExtraCrops property gets/sets the value of the double field ChanceForExtraCrops </value>
        public double ChanceForExtraCrops
        {
            get { return AsDynamic._GetChanceForExtraCrops(); }
            set { AsDynamic._SetChanceForExtraCrops(value); }
        }

        /// <summary>
        ///     The current phase of this crops growth cycle
        ///     Typical crops have 5 phases of growth, as visualised by their growing sprites
        /// </summary>
        /// <value>The CurrentPhase property gets/sets the value of the int field currentPhase</value>
        public int CurrentPhase
        {
            get { return AsDynamic._GetCurrentPhase(); }
            set { AsDynamic._SetCurrentPhase(value); }
        }

        /// <summary>
        ///     The current day of the current phase of the Crop.
        /// </summary>
        /// <value>The DayOfCurrentPhase property gets/sets the value of the int field dayOfCurrentPhase</value>
        public int DayOfCurrentPhase
        {
            get { return AsDynamic._GetDayOfCurrentPhase(); }
            set { AsDynamic._SetCurrentPhase(value); }
        }

        /// <summary>
        ///     A list of phase days of the Crop.
        /// </summary>
        /// <value>The PhaseDays property gets/sets the value of the List<int> field phaseDays</value>
        public ProxyList<int> PhaseDays
        {
            get
            {
                var tmp = AsDynamic._GetPhaseDays();
                if (tmp == null) return null;
                return new ProxyList<int>(tmp);
            }
        }

        /// <summary>
        ///     Whether this crop is dead or not
        /// </summary>
        /// <value>The IsDead property gets/sets the value of the bool field IsDead</value>
        public bool IsDead
        {
            get { return AsDynamic._GetDead(); }
            set { AsDynamic._SetDead(true); }
        }

        public bool Flip
        {
            get { return AsDynamic._GetFlip(); }
            set { AsDynamic._SetFlip(value); }
        }

        public bool ForageCrop
        {
            get { return AsDynamic._GetForageCrop(); }
            set { AsDynamic._SetForageCrop(value); }
        }

        /// <summary>
        ///     Whether this crop is fully grown or not
        /// </summary>
        /// <value>The IsFullyGrown property gets/sets the value of the bool field IsFullyGrown</value>
        public bool IsFullyGrown
        {
            get { return AsDynamic._GetFullyGrown(); }
            set { AsDynamic._SetFullyGrown(value); }
        }

        public int HarvestMethod
        {
            get { return AsDynamic._GetHarvestMethod(); }
            set { AsDynamic._SetHarvestMethod(value); }
        }

        public int IndexOfHarvest
        {
            get { return AsDynamic._GetIndexOfHarvest(); }
            set { AsDynamic._SetIndexOfHarvest(value); }
        }

        public int MaxHarvest
        {
            get { return AsDynamic._GetMaxHarvest(); }
            set { AsDynamic._SetMaxHarvest(value); }
        }

        public int MaxHarvestIncreasePerFarmingLevel
        {
            get { return AsDynamic._GetMaxHarvestIncreasePerFarmingLevel(); }
            set { AsDynamic._SetMaxHarvestIncreasePerFarmingLevel(value); }
        }

        public int MinHarvest
        {
            get { return AsDynamic._GetMinHarvest(); }
            set { AsDynamic._SetMinHarvest(value); }
        }

        public int PhaseToShow
        {
            get { return AsDynamic._GetPhaseToShow(); }
            set { AsDynamic._SetPhaseToShow(value); }
        }

        public bool ProgramColored
        {
            get { return AsDynamic._GetProgramColored(); }
            set { AsDynamic._SetProgramColored(value); }
        }

        public bool HasRaisedSeeds
        {
            get { return AsDynamic._GetRaisedSeeds(); }
            set { AsDynamic._SetRaisedSeeds(value); }
        }

        public int RegrowAfterHarvest
        {
            get { return AsDynamic._GetRegrowAfterHarvest(); }
            set { AsDynamic._SetRegrowAfterHarvest(value); }
        }

        public int RowInSpriteSheet
        {
            get { return AsDynamic._GetRowInSpriteSheet(); }
            set { AsDynamic._SetRowInSpriteSheet(value); }
        }

        public ProxyList<string> SeasonsToGrowIn
        {
            get
            {
                var tmp = AsDynamic._GetSeasonsToGrowIn();
                if (tmp == null) return null;
                return new ProxyList<string>(tmp);
            }
        }

        /// <summary>
        ///     Grows the crop completely instantly
        /// </summary>
        public void GrowCompletely()
        {
            AsDynamic._GrowCompletely();
        }

        public bool Harvest(int xTile, int yTile, object soil)
        {
            return AsDynamic._Harvest(xTile, yTile, soil);
        }

        public bool Harvest(int xTile, int yTile, HoeDirt soil)
        {
            return Harvest(xTile, yTile, soil.Underlying);
        }
    }
}