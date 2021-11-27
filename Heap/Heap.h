#include <algorithm>
#include <string>
#include <vector>
#pragma once

using namespace std;

template <typename T> T get_sentinel();

template <typename T> class Heap {
protected:
  static const int INIT_HEAP_CAPACITY = 128;
  vector<T> _elems;
  size_t _size;

  bool _percolate_down(size_t pos) {
    // leaf
    if (pos * 2 > _size)
      return false;

    // only has left child
    if (pos * 2 == _size) {
      if (_elems[2 * pos] < _elems[pos]) {
        swap(_elems[pos], _elems[2 * pos]);
        return true;
      }
      return false;
    }

    // has both child
    if (_elems[pos] < _elems[2 * pos] && _elems[pos] < _elems[2 * pos + 1])
      return false;

    size_t next = _elems[2 * pos + 1] < _elems[2 * pos] ? 2 * pos + 1 : 2 * pos;
    swap(_elems[pos], _elems[next]);
    _percolate_down(next);
    return true;
  }

  bool _heapify() {
    bool any = false;
    for (int i = (_size + 1) / 2; i >= 0; i--)
      any |= _percolate_down(i + 1);
    return any;
  }

public:
  Heap() {
    _elems.resize(INIT_HEAP_CAPACITY);
    _elems[0] = get_sentinel<T>();
    _size = 0;
  };

  Heap(const vector<T> &vec) {
    _elems.push_back(get_sentinel<T>());
    for (const T &v : vec)
      _elems.push_back(v);
    _size = vec.size();
    _heapify();
  }

  virtual bool is_empty() const { return _size == 0; }
  virtual bool insert(const T &elem) {
    if (++_size == _elems.size()) {
      _elems.resize(2 * _elems.size());
    }
    _elems[_size] = elem;
    size_t pos = _size;
    while (_elems[pos] < _elems[pos / 2]) {
      swap(_elems[pos], _elems[pos / 2]);
      pos /= 2;
    }
    return true;
  }

  virtual bool delete_min() {
    if (_size == 0)
      return false;

    // if (max(--_size, (size_t)INIT_HEAP_CAPACITY / 4) < _elems.size() / 4)
    // _elems.resize(_elems.size() / 2);

    _elems[1] = _elems[_size];
    _percolate_down(1);
    _size--;
    return true;
  }

  virtual const T &peek_min() const {
    return _size == 0 ? _elems[0] : _elems[1];
  }

  virtual string to_string() const { return ""; };

  friend class Tests;
};
