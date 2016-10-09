/*
    Copyright 2016 Matt Stevens (Handsome Matt), Inari-Whitebear

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

namespace Storm.StardewValley.Wrapper
{
    public class ChatBox : ClickableMenu
    {
        public ChatBox(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public ChatBox()
        {
        }

        public void ReceiveChatMessage(string message, long who)
        {
            AsDynamic._ReceiveChatMessage(message, who);
        }
    }
}