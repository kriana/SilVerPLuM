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

using Microsoft.Xna.Framework;

namespace Storm.StardewValley.Wrapper
{
    public class HudMessage : StaticContextWrapper
    {
        public HudMessage(StaticContext parent, object accessor) : base(parent)
        {
            Underlying = accessor;
        }

        public HudMessage()
        {
        }

        public string Message
        {
            get { return AsDynamic._GetMessage(); }
            set { AsDynamic._SetMessage(value); }
        }

        public string Type
        {
            get { return AsDynamic._GetType(); }
            set { AsDynamic._SetType(value); }
        }

        public Color Color
        {
            get { return AsDynamic._GetColor(); }
            set { AsDynamic._SetColor(value); }
        }

        public float TimeLeft
        {
            get { return AsDynamic._GetTimeLeft(); }
            set { AsDynamic._SetTimeLeft(value); }
        }

        public float Transparency
        {
            get { return AsDynamic._GetTransparency(); }
            set { AsDynamic._SetTransparency(value); }
        }

        public int Number
        {
            get { return AsDynamic._GetNumber(); }
            set { AsDynamic._SetNumber(value); }
        }

        public int WhatType
        {
            get { return AsDynamic._GetWhatType(); }
            set { AsDynamic._SetWhatType(value); }
        }

        public bool Add
        {
            get { return AsDynamic._GetAdd(); }
            set { AsDynamic._SetAdd(value); }
        }

        public bool Achievement
        {
            get { return AsDynamic._GetAchievement(); }
            set { AsDynamic._SetAchievement(value); }
        }

        public bool FadeIn
        {
            get { return AsDynamic._GetFadeIn(); }
            set { AsDynamic._SetFadeIn(value); }
        }

        public bool NoIcon
        {
            get { return AsDynamic._GetNoIcon(); }
            set { AsDynamic._SetNoIcon(value); }
        }
    }
}
