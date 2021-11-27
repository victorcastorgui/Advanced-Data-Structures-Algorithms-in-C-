
#include "Hash_Table_LP.h"
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

#ifndef Hash_Table_QP_h
#define Hash_Table_QP_h

using namespace std;

template <typename T> class Hash_Table_QP : public Hash_Table_LP<T> {
public:
  Hash_Table_QP(size_t n = Hash_Table_LP<T>::DEFAULT_INIT_CAPACITY)
      : Hash_Table_LP<T>(n) {
    this->_max_load_factor = _get_biggest_allowed_max_load_factor();
  }

protected:
  virtual float _get_biggest_allowed_max_load_factor() const { return 0.5; }

  virtual size_t _find_pos(const T &item) const {
    size_t current = (this->_get_hash_modulus(item));
    if ((this->_elems.size() - this->_num_non_vacant_cells) == 0)
      return string::npos;
    size_t temp = 1;
    while ((this->_elems[current]._state) == Hash_Table_LP<T>::Entry::DELETED ||
           (this->_elems[current]._state) == Hash_Table_LP<T>::Entry::ACTIVE) {
      if ((this->_elems[current]._data) == item) {
        return current;
      }
      current += temp;
      temp += 2;
      current = current % (this->_elems.size());
    }
    return current;
  }

  static size_t _next_prime(size_t n) {
    n++;
    for (;; n++) {
      if (n == 2 || n == 3)
        return n;
      else if (n == 1)
        continue;
      else if (n % 2 == 0 || n % 3 == 0)
        continue;
      bool caci = true;
      int i;
      for (i = 6; i <= sqrt(n) + 1; i += 6) {
        if (n % (i + 1) == 0 || n % (i - 1) == 0) {
          caci = false;
          break;
        }
      }
      if (caci == true)
        return n;
    }
  }

  friend class Tests;
};

#endif /* Hash_Table_QP_h */
