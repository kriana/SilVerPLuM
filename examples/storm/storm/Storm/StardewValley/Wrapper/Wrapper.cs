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

using System;

namespace Storm.StardewValley.Wrapper
{
    public class Wrapper
    {
        public object Underlying { get; set; }

        public dynamic AsDynamic => Underlying;

        public bool IsNull() => Underlying == null;

        public virtual T As<TA, T>() where T : Wrapper
        {
            var instance = (T) Activator.CreateInstance(typeof(T));
            return As<TA, T>(instance);
        }

        public virtual T As<TA, T>(T instance) where T : Wrapper
        {
            instance.Underlying = Underlying;
            return instance;
        }
    }
}