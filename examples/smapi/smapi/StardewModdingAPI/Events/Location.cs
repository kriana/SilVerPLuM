using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using StardewValley;
using Object = StardewValley.Object;

namespace StardewModdingAPI.Events
{
    public static class LocationEvents
    {
        public static event EventHandler<EventArgsGameLocationsChanged> LocationsChanged = delegate { };
        public static event EventHandler<EventArgsLocationObjectsChanged> LocationObjectsChanged = delegate { };
        public static event EventHandler<EventArgsCurrentLocationChanged> CurrentLocationChanged = delegate { };

        internal static void InvokeLocationsChanged(List<GameLocation> newLocations)
        {
            LocationsChanged.Invoke(null, new EventArgsGameLocationsChanged(newLocations));
        }

        internal static void InvokeCurrentLocationChanged(GameLocation priorLocation, GameLocation newLocation)
        {
            CurrentLocationChanged.Invoke(null, new EventArgsCurrentLocationChanged(priorLocation, newLocation));
        }

        internal static void InvokeOnNewLocationObject(SerializableDictionary<Vector2, Object> newObjects)
        {
            LocationObjectsChanged.Invoke(null, new EventArgsLocationObjectsChanged(newObjects));
        }
    }
}