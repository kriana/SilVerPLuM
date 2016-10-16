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

using System.Collections;
using Microsoft.Xna.Framework;
using Storm.Collections;

namespace Storm.StardewValley.Wrapper
{
    public class GameLocation : StaticContextWrapper
    {
        public GameLocation(StaticContext parent, object accessor) : base(parent)
        {
            Underlying = accessor;
        }

        public GameLocation()
        {
        }

        public ValueProxyDictionary<Vector2, object, ObjectItem> Objects
        {
            get
            {
                var tmp = AsDynamic._GetObjects();
                if (tmp == null) return null;
                return new ValueProxyDictionary<Vector2, object, ObjectItem>((IDictionary) tmp, o => o == null ? null : new ObjectItem(Parent, o));
            }
        }

        public ValueProxyDictionary<Vector2, object, TerrainFeature> TerrainFeatures
        {
            get
            {
                var tmp = AsDynamic._GetTerrainFeatures();
                if (tmp == null) return null;
                return new ValueProxyDictionary<Vector2, object, TerrainFeature>((IDictionary) tmp, tf => tf == null ? null : new TerrainFeature(Parent, tf));
            }
        }

        public WrappedProxyList<object, Npc> Characters
        {
            get
            {
                var tmp = AsDynamic._GetCharacters();
                if (tmp == null) return null;
                return new WrappedProxyList<object, Npc>((IList) tmp, c => c == null ? null : new Npc(Parent, c));
            }
        }

        public bool IsOutdoors
        {
            get { return AsDynamic._GetIsOutdoors(); }
            set { AsDynamic._SetIsOutdoors(value); }
        }

        public string Name
        {
            get { return AsDynamic._GetName(); }
            set { AsDynamic._SetName(value); }
        }

        public Event CurrentEvent
        {
            get
            {
                var tmp = AsDynamic._GetCurrentEvent();
                if (tmp == null) return null;
                return new Event(Parent, tmp);
            }
            set { AsDynamic._SetCurrentEvent(value?.Underlying); }
        }

        public ObjectItem GetObjectAt(int tileX, int tileY)
        {
            var key = new Vector2(tileX/Parent.TileSize, tileY/Parent.TileSize);
            var objects = Objects;
            return objects.ContainsKey(key) ? objects[key] : null;
        }

        public void AddHoeDirtAt(Vector2 tileLocation)
        {
            AsDynamic._MakeHoeDirt(tileLocation);
        }

        public string GetTileProperty(int tileX, int tileY, string propName, string layerName)
        {
            return AsDynamic._GetTileProperty(tileX, tileY, propName, layerName);
        }

        public void GrowWeedGrass(int iterations)
        {
            AsDynamic._GrowWeedGrass(iterations);
        }
    }
}