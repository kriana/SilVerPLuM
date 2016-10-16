using System;
using System.Collections.Generic;
using StardewModdingAPI.Inheritance;
using StardewValley;

namespace StardewModdingAPI.Events
{
    public static class PlayerEvents
    {
        public static event EventHandler<EventArgsFarmerChanged> FarmerChanged = delegate { };
        public static event EventHandler<EventArgsInventoryChanged> InventoryChanged = delegate { };
        public static event EventHandler<EventArgsLevelUp> LeveledUp = delegate { };
        public static event EventHandler<EventArgsLoadedGameChanged> LoadedGame = delegate { };

        internal static void InvokeFarmerChanged(Farmer priorFarmer, Farmer newFarmer)
        {
            FarmerChanged.Invoke(null, new EventArgsFarmerChanged(priorFarmer, newFarmer));
        }

        internal static void InvokeInventoryChanged(List<Item> inventory, List<ItemStackChange> changedItems)
        {
            InventoryChanged.Invoke(null, new EventArgsInventoryChanged(inventory, changedItems));
        }

        internal static void InvokeLeveledUp(EventArgsLevelUp.LevelType type, int newLevel)
        {
            LeveledUp.Invoke(null, new EventArgsLevelUp(type, newLevel));
        }

        internal static void InvokeLoadedGame(EventArgsLoadedGameChanged loaded)
        {
            LoadedGame.Invoke(null, loaded);
        }
    }
}