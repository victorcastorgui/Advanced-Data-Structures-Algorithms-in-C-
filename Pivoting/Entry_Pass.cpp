
#include "Pivoting.h"
#include <algorithm>
#include <vector>
using namespace std;

void my_questing_sort_in_place(vector<int> &elems) {
  sort(elems.begin(), elems.end());
  // Pivoting<int>::do_qsort(elems);
}
