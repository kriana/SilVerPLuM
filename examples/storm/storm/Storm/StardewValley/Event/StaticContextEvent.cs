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

using System.Reflection;
using Storm.ExternalEvent;
using Storm.Manipulation;
using Storm.StardewValley.Wrapper;

namespace Storm.StardewValley.Event
{
    public class StaticContextEvent : DetourEvent
    {
        public delegate void InitDelegate(StaticContextEvent @this);

        public StaticContextEvent(params object[] @params)
        {
            Params = @params;
        }

        public Assembly GameAssembly { get; set; }
        public StaticContext Root { get; set; }
        public EventBus EventBus { get; set; }
        public object[] Params { get; set; }

        public Farmer LocalPlayer => Root.Player;

        public GameLocation Location => Root.CurrentLocation;

        public void Init(InitDelegate init)
        {
            init(this);
        }

        public T GetParameter<T>(int index)
        {
            return (T) Params[index];
        }
    }
}