﻿using Microsoft.Xna.Framework;
using StardewValley;

namespace Pathoschild.LookupAnything.Framework.Constants
{
    /// <summary>Constant mod values.</summary>
    internal static class Constant
    {
        /*********
        ** Accessors
        *********/
        /// <summary>The minimum supported version of Stardew Valley.</summary>
        public static string MinimumGameVersion = "1.1";

        /// <summary>The minimum supported version of SMAPI.</summary>
        public static string MinimumApiVersion = "0.40.0 1.1";

        /// <summary>The largest expected sprite size (measured in tiles).</summary>
        /// <remarks>This is used to account for sprites that extend beyond their tile when searching for targets. These values should be large enough to cover the largest target sprites, but small enough to minimise expensive cursor collision checks.</remarks>
        public static readonly Vector2 MaxTargetSpriteSize = new Vector2(3, 5);

        /// <summary>The <see cref="Farmer.mailReceived"/> keys referenced by the mod.</summary>
        public static class MailLetters
        {
            /// <summary>Set when the spouse gives the player a stardrop.</summary>
            public const string ReceivedSpouseStardrop = "CF_Spouse";
        }

        /// <summary>The season names.</summary>
        public static class SeasonNames
        {
            /// <summary>The internal name for Spring.</summary>
            public const string Spring = "spring";

            /// <summary>The internal name for Summer.</summary>
            public const string Summer = "summer";

            /// <summary>The internal name for Fall.</summary>
            public const string Fall = "fall";

            /// <summary>The internal name for Winter.</summary>
            public const string Winter = "winter";
        }

        /// <summary>The names of items referenced by the mod.</summary>
        public static class ItemNames
        {
            /// <summary>The internal name for the heater object.</summary>
            public static string Heater = "Heater";
        }

        /// <summary>The names of locations referenced by the mod.</summary>
        public static class LocationNames
        {
            /// <summary>The internal name for the greenhouse.</summary>
            public static string Greenhouse = "Greenhouse";
        }

        /// <summary>The names of buildings referenced by the mod.</summary>
        public static class BuildingNames
        {
            /// <summary>The internal name for the Gold Clock.</summary>
            public static string GoldClock = "Gold Clock";
        }
    }
}
