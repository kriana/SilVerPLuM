using System;
using StardewValley.Menus;

namespace StardewModdingAPI.Events
{
    public static class MenuEvents
    {
        public static event EventHandler<EventArgsClickableMenuChanged> MenuChanged = delegate { };
        public static event EventHandler<EventArgsClickableMenuClosed> MenuClosed = delegate { };

        internal static void InvokeMenuChanged(IClickableMenu priorMenu, IClickableMenu newMenu)
        {
            MenuChanged.Invoke(null, new EventArgsClickableMenuChanged(priorMenu, newMenu));
        }

        internal static void InvokeMenuClosed(IClickableMenu priorMenu)
        {
            MenuClosed.Invoke(null, new EventArgsClickableMenuClosed(priorMenu));
        }
    }
}