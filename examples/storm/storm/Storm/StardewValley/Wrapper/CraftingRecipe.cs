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
    public class CraftingRecipe : StaticContextWrapper
    {
        public CraftingRecipe(StaticContext parent, object accessor) :
            base(parent)
        {
            Underlying = accessor;
        }

        public CraftingRecipe()
        {
        }

        public string Name
        {
            get { return AsDynamic._GetName(); }
            set { AsDynamic._SetName(value); }
        }

        public string Description
        {
            get { return AsDynamic._GetDescription(); }
            set { AsDynamic._SetDescription(value); }
        }

        public ProxyDictionary<string, string> CraftingRecipes
        {
            get
            {
                var tmp = AsDynamic._GetCraftingRecipes();
                return tmp == null ? null : new ProxyDictionary<string, string>(tmp);
            }
        }

        public ProxyDictionary<string, string> CookingRecipes
        {
            get
            {
                var tmp = AsDynamic._GetCookingRecipes();
                return tmp == null ? null : new ProxyDictionary<string, string>(tmp);
            }
        }

        public ProxyDictionary<int, int> RecipeList
        {
            get
            {
                var tmp = AsDynamic._GetRecipeList();
                return tmp == null ? null : new ProxyDictionary<int, int>(tmp);
            }
        }

        public ProxyList<int> ItemToProduce
        {
            get
            {
                var tmp = AsDynamic._GetItemToProduce();
                return tmp == null ? null : new ProxyList<int>(tmp);
            }
        }

        public bool BigCraftable
        {
            get { return AsDynamic._GetBigCraftable(); }
            set { AsDynamic._SetBigCraftable(value); }
        }

        public bool IsCookingRecipe
        {
            get { return AsDynamic._GetIsCookingRecipe(); }
            set { AsDynamic._SetIsCookingRecipe(value); }
        }

        public int TimesCrafted
        {
            get { return AsDynamic._GetTimesCrafted(); }
            set { AsDynamic._SetTimesCrafted(value); }
        }

        public int NumberProducedPerCraft
        {
            get { return AsDynamic._GetNumberProducedPerCraft(); }
            set { AsDynamic._SetNumberProducedPerCraft(value); }
        }
    }
}