
#include <cstdio>
#include <vector>
using namespace std;

template <typename T> class Pivoting {
private:
  static size_t _partition(vector<T> &elems, size_t lo, size_t hi);
  static T _find_kth_least_elem(vector<T> &elems, size_t lo, size_t hi,
                                size_t k);
  static void _do_qsort(vector<T> &elems, size_t lo, size_t hi);

public:
  static T find_median(vector<T> &elems);
  static T find_kth_least_elem(vector<T> &elems, size_t k);
  static void do_qsort(vector<T> &elems);

  friend class Tests;
};

template <typename T>
size_t Pivoting<T>::_partition(vector<T> &v, size_t lo, size_t hi) {
  size_t pivot_index = lo + (hi - lo) / 2;
  T pivot = v[pivot_index];
  size_t i = lo;
  size_t j = hi;
  while (true) {
    while (i < hi && v[i] < pivot) i++;
    while (j > lo && v[j] > pivot) j--;
    if (i >= j) return j;
    swap(v[i++], v[j--]);
  }
}

template <typename T>
T Pivoting<T>::_find_kth_least_elem(vector<T> &elems, size_t lo, size_t hi,
                                    size_t k) {
  if (lo == hi)
    return elems[hi];
  size_t cut = _partition(elems, lo, hi);
  if (cut - lo >= k)
    return _find_kth_least_elem(elems, lo, cut, k);
  return _find_kth_least_elem(elems, cut + 1, hi, k - cut + lo - 1);
}

template <typename T>
void Pivoting<T>::_do_qsort(vector<T> &elems, size_t lo, size_t hi) {
  if (lo >= hi)
    return;
  size_t cut = _partition(elems, lo, hi);
  _do_qsort(elems, lo, cut);
  _do_qsort(elems, cut + 1, hi);
}

template <typename T> T Pivoting<T>::find_median(vector<T> &elems) {
  T rv = find_kth_least_elem(elems, elems.size() / 2);
  return rv;
}

template <typename T>
T Pivoting<T>::find_kth_least_elem(vector<T> &elems, size_t k) {
    if (k < 0 || k >= elems.size()) return T();
  return _find_kth_least_elem(elems, 0, elems.size() - 1, k);
}

template <typename T> void Pivoting<T>::do_qsort(vector<T> &elems) {
  return _do_qsort(elems, 0, elems.size() - 1);
}
