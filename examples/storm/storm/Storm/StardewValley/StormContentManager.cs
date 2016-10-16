/*
    Copyright 2016 Matthew Bell, Cody R (Demmonic)

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

using Microsoft.Xna.Framework.Content;
using Storm.StardewValley.Event;

namespace Storm.StardewValley
{
    public static class StormContentManager
    {
        public static T Load<T>(ContentManager manager, string assetName)
        {
            var @event = new StaticContextEvent(manager, assetName);
            StaticGameContext.FireEvent("content_on_load", @event);
            if (@event.ReturnValue != null)
            {
                return (T) @event.ReturnValue;
            }
            return manager.Load<T>(assetName);
        }

        public static void Unload(ContentManager manager)
        {
            var @event = new StaticContextEvent();
            StaticGameContext.FireEvent("content_on_unload", @event);
            manager.Unload();
        }
    }
}