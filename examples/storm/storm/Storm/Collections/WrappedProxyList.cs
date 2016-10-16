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
using Storm.StardewValley.Wrapper;

namespace Storm.Collections
{
    public class WrappedProxyList<TOValue, TValue> : IList<TValue> where TValue : Wrapper
    {
        public delegate TW Wrap<in TV, out TW>(TV val);

        private readonly Wrap<TOValue, TValue> _wrapper;

        public WrappedProxyList(IList real, Wrap<TOValue, TValue> wrapper)
        {
            Real = real;
            _wrapper = wrapper;
        }

        internal IList Real { get; }

        public int Count => Real.Count;

        public bool IsReadOnly => false;

        public TValue this[int index]
        {
            get { return _wrapper((TOValue) Real[index]); }

            set { Real[index] = value?.Underlying; }
        }

        public int IndexOf(TValue item)
        {
            return Real.IndexOf(item.Underlying);
        }

        public void Insert(int index, TValue item)
        {
            Real.Insert(index, item?.Underlying);
        }

        public void RemoveAt(int index)
        {
            Real.RemoveAt(index);
        }

        public void Add(TValue item)
        {
            Real.Add(item?.Underlying);
        }

        public void Clear()
        {
            Real.Clear();
        }

        public bool Contains(TValue item)
        {
            return Real.Contains(item.Underlying);
        }

        public void CopyTo(TValue[] array, int arrayIndex)
        {
            throw new NotImplementedException();
        }

        public bool Remove(TValue item)
        {
            if (!Contains(item)) return false;
            Real.Remove(item.Underlying);
            return true;
        }

        public IEnumerator<TValue> GetEnumerator()
        {
            return new ProxyEnumerator<TOValue, TValue>(Real, _wrapper);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            throw new NotImplementedException();
        }

        private class ProxyEnumerator<TEoValue, TEValue> : IEnumerator<TEValue>
        {
            private readonly IList _real;
            private readonly Wrap<TEoValue, TEValue> _wrapper;
            private int _curIndex;
            private TEoValue _curValue;

            public ProxyEnumerator(IList real, Wrap<TEoValue, TEValue> wrapper)
            {
                _real = real;
                _wrapper = wrapper;
                _curIndex = -1;
                _curValue = default(TEoValue);
            }

            public TEValue Current => _wrapper(_curValue);

            object IEnumerator.Current => _curValue;

            public void Dispose() { }

            public bool MoveNext()
            {
                if (++_curIndex >= _real.Count)
                {
                    return false;
                }
                _curValue = (TEoValue) _real[_curIndex];
                return true;
            }

            public void Reset()
            {
                _curIndex = -1;
            }
        }
    }
}