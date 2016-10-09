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
using Microsoft.Xna.Framework.Graphics;

namespace Storm.StardewValley.Wrapper
{
    public class Tool : Item
    {
        public Tool(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public Tool()
        {
        }

        public ObjectItem[] Attachments
        {
            get { return Array.ConvertAll((object[]) AsDynamic._GetAttachments(), i => new ObjectItem(Parent, i)); }
            set { AsDynamic._SetAttachments(Array.ConvertAll(value, i => i.Underlying)); }
        }

        /// <summary>
        ///     The name of this tool
        /// </summary>
        /// <value>The Name property gets/sets the value of the string field Name</value>
        public string Name
        {
            get { return AsDynamic._GetName(); }
            set { AsDynamic._SetName(value); }
        }

        /// <summary>
        ///     The description of this tool
        /// </summary>
        /// <value>The Description propertly gets/sets the value of the string field Description</value>
        public new string Description
        {
            get { return AsDynamic._GetDescription(); }
            set { AsDynamic._SetDescription(value); }
        }

        public bool IsStackable
        {
            get { return AsDynamic._GetStackable(); }
            set { AsDynamic._SetStackable(value); }
        }

        /// <summary>
        ///     The upgrade level of this tool
        ///     Default = 0
        ///     Copper = 1
        ///     Iron = 2
        ///     Gold = 3
        ///     Iridium = 4
        /// </summary>
        /// <value>The UpgradeLevel property sets/gets the value of the int field UpgradeLevel</value>
        public int UpgradeLevel
        {
            get { return AsDynamic._GetUpgradeLevel(); }
            set { AsDynamic._SetUpgradeLevel(value); }
        }

        public Texture2D WeaponTexture
        {
            get { return AsDynamic._GetWeaponsTexture(); }
            set { AsDynamic._SetWeaponsTexture(value); }
        }

        public Farmer LastUser
        {
            get
            {
                var tmp = AsDynamic._GetLastUser();
                if (tmp == null) return null;
                return new Farmer(Parent, tmp);
            }
            set { AsDynamic._SetLastUser(value?.Underlying); }
        }
    }
}