#include "Heap.h"
#include <string>
#include <vector>
#pragma once
using namespace std;

template <typename T> class Special_Heap : public Heap<T> {
  Special_Heap() : Heap<T>(){};
  Special_Heap(const vector<T> &vec) : Heap<T>(vec){};

  const vector<T> &get_least_k(size_t k) {
    if (k > this->_size)
      return this->_elems;

    for (size_t i = 0; i < k; i++) {
      T v = this->peek_min();
      this->delete_min();
      this->_elems[this->_size + 1] = v;
    }

    this->_size = 0;
    return this->_elems;
  };

  friend class Tests;
};
