/*
    Copyright 2016 Cody R. (Demmonic)

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

namespace Storm.Manipulation.Json
{
    public class JsonEventCallbackParams
    {
        public string OwnerAccessorType { get; set; }
        public string OwnerMethodName { get; set; }
        public string OwnerMethodDesc { get; set; }
        public string EventId { get; set; } = "NA";
        public bool PushParams { get; set; }
        public bool RedirectBranching { get; set; } = false;
        public InsertionType InsertionType { get; set; }
        public int[] InsertionIndex { get; set; }
    }
}