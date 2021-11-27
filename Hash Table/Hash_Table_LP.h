
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#ifndef Hash_Table_LP_h
#define Hash_Table_LP_h

using namespace std;
template <typename T> size_t Hash(const T &item) { return 0; }

template <typename T> class Hash_Table_LP {
protected:
  struct Entry {
    T _data;
    enum STATE { ACTIVE, VACANT, DELETED } _state;
    Entry(const T &d = T(), STATE st = VACANT) : _data(d), _state(st) {}
  };

  static const size_t DEFAULT_INIT_CAPACITY = 3;
  vector<Entry> _elems;
  size_t _size;
  size_t _num_non_vacant_cells;
  float _max_load_factor;

  virtual size_t _get_hash_modulus(const T &item) const {
    return (Hash(item)) % (_elems.size());
  }
  virtual void _rehash() {
    vector<Entry> victor = _elems;
    _grow_capacity();
    for (size_t i = 0; i < _elems.size(); i++) {
      _elems[i]._state = Entry::VACANT;
    }
    _size = 0;
    _num_non_vacant_cells = 0;

    for (size_t i = 0; i < victor.size(); i++) {
      if (victor[i]._state == Entry::ACTIVE) {
        insert(victor[i]._data);
      }
    }
    return;
  }

  virtual bool set_max_load_factor(float x) {
    if (x <= 0)
      return false;
    else if (x > _get_biggest_allowed_max_load_factor())
      return false;
    _max_load_factor = x;
    return true;
  }

  virtual float _get_biggest_allowed_max_load_factor() const { return 0.75; }

  virtual size_t _find_pos(const T &item) const {
    if ((_elems.size() - _num_non_vacant_cells) == 0)
      return string::npos;
    size_t current = _get_hash_modulus(item);
    for (; _elems[current]._state == Entry::DELETED ||
           _elems[current]._state == Entry::ACTIVE;
         current = ((current + 1) % _elems.size())) {
      if (_elems[current]._data == item) {
        return current;
      }
    }
    return current;
  }

  virtual void _grow_capacity() { _elems.resize((_elems.size()) * 2); }

public:
  Hash_Table_LP(size_t n = DEFAULT_INIT_CAPACITY) {
    _elems.resize(n);
    _size = 0;
    _num_non_vacant_cells = 0;
    _max_load_factor = 0.75;
  }
  size_t get_size() const { return _size; }
  bool is_empty() const { return _size == 0; }
  bool contains(const T &item) const {
    size_t current = _find_pos(item);
    if (current == string::npos)
      return false;
    else if (_elems[current]._state == Entry::VACANT ||
             _elems[current]._state == Entry::DELETED)
      return false;
    return true;
  }

  T &find(const T &item) {
    size_t current = _find_pos(item);
    if (current == string::npos)
      throw Table_full_exception();
    else if (_elems[current]._state == Entry::VACANT)
      throw Not_found_exception();
    return _elems[current]._data;
  }

  bool clear() { return false; }

  bool insert(const T &item) {
    size_t current = _find_pos(item);
    if (current == string::npos)
      return false;
    else if (_elems[current]._state == Entry::ACTIVE)
      return false;
    else if (_elems[current]._state == Entry::DELETED) {
      _elems[current]._state = Entry::ACTIVE;
      _size++;
      return true;
    }
    _elems[current]._data = item;
    _elems[current]._state = Entry::ACTIVE;
    _size++;
    _num_non_vacant_cells++;
    if (_num_non_vacant_cells > _elems.size() * _max_load_factor)
      _rehash();
    return true;
  }

  bool remove(const T &item) {
    size_t current = _find_pos(item);
    if (current == string::npos)
      return false;
    else if (_elems[current]._state == Entry::ACTIVE) {
      _elems[current]._state = Entry::DELETED;
      _size--;
      return true;
    }
    return false;
  }

  class Table_full_exception : public exception {
  public:
    const string to_string() const throw() {
      return string("Table full exception");
    }
  };
  class Not_found_exception : public exception {
  public:
    const string to_string() const throw() {
      return string("Not found exception");
    }
  };

  friend class Tests;
};

#endif /* Hash_Table_LP_h */
