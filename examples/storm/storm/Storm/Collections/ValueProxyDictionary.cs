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
    public class ValueProxyDictionary<TKey, TOValue, TValue> : IDictionary<TKey, TValue> where TValue : Wrapper
    {
        public delegate TW Wrap<in TV, out TW>(TV val);

        private readonly IDictionary _real;
        private readonly Wrap<TOValue, TValue> _wrapper;

        public ValueProxyDictionary(IDictionary real, Wrap<TOValue, TValue> wrapper)
        {
            _real = real;
            _wrapper = wrapper;
        }

        public ICollection<TKey> Keys
        {
            get
            {
                var list = new List<TKey>();
                foreach (var key in _real.Keys)
                {
                    list.Add((TKey) key);
                }
                return list;
            }
        }

        public ICollection<TValue> Values
        {
            get
            {
                var list = new List<TValue>();
                foreach (var value in _real.Values)
                {
                    list.Add(_wrapper((TOValue) value));
                }
                return list;
            }
        }

        public int Count => _real.Count;

        public bool IsReadOnly => false;

        public TValue this[TKey key]
        {
            get { return _wrapper((TOValue) _real[key]); }

            set { _real[key] = value.Underlying; }
        }

        public bool ContainsKey(TKey key)
        {
            return _real.Contains(key);
        }

        public void Add(TKey key, TValue value)
        {
            _real.Add(key, value.Underlying);
        }

        public bool Remove(TKey key)
        {
            if (!ContainsKey(key)) return false;
            _real.Remove(key);
            return true;
        }

        public bool TryGetValue(TKey key, out TValue value)
        {
            if (!ContainsKey(key))
            {
                value = default(TValue);
                return false;
            }
            value = this[key];
            return true;
        }

        public void Add(KeyValuePair<TKey, TValue> item)
        {
            _real.Add(item.Key, item.Value.Underlying);
        }

        public void Clear()
        {
            _real.Clear();
        }

        public bool Contains(KeyValuePair<TKey, TValue> item)
        {
            foreach (var key in _real.Keys)
            {
                if (key.Equals(item.Key) && _real[key].Equals(item.Value.Underlying))
                {
                    return true;
                }
            }
            return false;
        }

        public void CopyTo(KeyValuePair<TKey, TValue>[] array, int arrayIndex)
        {
            throw new NotImplementedException();
        }

        public bool Remove(KeyValuePair<TKey, TValue> item)
        {
            foreach (var key in _real.Keys)
            {
                if (key.Equals(item.Key) && _real[key].Equals(item.Value.Underlying))
                {
                    _real.Remove(item.Key);
                    return true;
                }
            }
            return false;
        }

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            return new ProxyEnumerator<TKey, TOValue, TValue>(_real, _wrapper);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            throw new NotImplementedException();
        }

        private class ProxyEnumerator<TEKey, TEoValue, TEValue> : IEnumerator<KeyValuePair<TEKey, TEValue>>
        {
            private readonly IList _keys;
            private readonly IDictionary _real;
            private readonly Wrap<TEoValue, TEValue> _wrapper;
            private int _curIndex;
            private TEKey _curKey;
            private TEoValue _curValue;

            public ProxyEnumerator(IDictionary real, Wrap<TEoValue, TEValue> wrapper)
            {
                _real = real;
                _wrapper = wrapper;
                _keys = new ArrayList();
                foreach (var key in real.Keys)
                {
                    _keys.Add(key);
                }
                _curIndex = -1;
                _curKey = default(TEKey);
                _curValue = default(TEoValue);
            }

            public KeyValuePair<TEKey, TEValue> Current => new KeyValuePair<TEKey, TEValue>(_curKey, _wrapper(_curValue));

            object IEnumerator.Current => _curValue;

            public void Dispose() { }

            public bool MoveNext()
            {
                if (++_curIndex >= _keys.Count)
                {
                    return false;
                }
                _curKey = (TEKey) _keys[_curIndex];
                _curValue = (TEoValue) _real[_curKey];
                return true;
            }

            public void Reset()
            {
                _curIndex = -1;
            }
        }
    }
}