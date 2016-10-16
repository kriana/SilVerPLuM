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

using System;
using System.Collections;
using System.Collections.Generic;

namespace Storm.Collections
{
    public class ProxyList<TValue> : IList<TValue>
    {
        private readonly IList _real;

        public ProxyList(IList real)
        {
            _real = real;
        }

        public int Count => _real.Count;

        public bool IsReadOnly => false;

        public TValue this[int index]
        {
            get { return (TValue) _real[index]; }

            set { _real[index] = value; }
        }

        public int IndexOf(TValue item)
        {
            return _real.IndexOf(item);
        }

        public void Insert(int index, TValue item)
        {
            _real.Insert(index, item);
        }

        public void RemoveAt(int index)
        {
            _real.RemoveAt(index);
        }

        public void Add(TValue item)
        {
            _real.Add(item);
        }

        public void Clear()
        {
            _real.Clear();
        }

        public bool Contains(TValue item)
        {
            return _real.Contains(item);
        }

        public void CopyTo(TValue[] array, int arrayIndex)
        {
            throw new NotImplementedException();
        }

        public bool Remove(TValue item)
        {
            if (!Contains(item)) return false;
            _real.Remove(item);
            return true;
        }

        public IEnumerator<TValue> GetEnumerator()
        {
            return new ProxyEnumerator<TValue>(_real);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            throw new NotImplementedException();
        }

        private class ProxyEnumerator<TEValue> : IEnumerator<TEValue>
        {
            private readonly IList _real;
            private int _curIndex;

            public ProxyEnumerator(IList real)
            {
                _real = real;
                _curIndex = -1;
                Current = default(TEValue);
            }

            public TEValue Current { get; private set; }

            object IEnumerator.Current => Current;

            public void Dispose() { }

            public bool MoveNext()
            {
                if (++_curIndex >= _real.Count)
                {
                    return false;
                }
                Current = (TEValue) _real[_curIndex];
                return true;
            }

            public void Reset()
            {
                _curIndex = -1;
            }
        }
    }
}