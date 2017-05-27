// Median of Medians
// get the k-th element in stable O(n) time
// Author: Czxck001 (github.com/Czxck001)
// g++ -std=c++14 mom.cc -o mom

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

const int GROUPSIZE = 5;

// need ‘typename’ before ‘std::vector<_RealType>::iterator’
// because ‘std::vector<_RealType>’ is a dependent scope
template <typename T>
using VIter = typename std::vector<T>::iterator;

template <typename T>
auto medianOfGroup(VIter<T> l, VIter<T> r) {
  // brutally get the median of a group A
  auto medLoc = l + GROUPSIZE / 2;
  for (auto i = l; i != medLoc + 1; ++i) {
    auto min = i;
    for (auto j = i + 1; j != r; ++j) {
      if (*min > *j) {
        min = j;
      }
    }
    std::iter_swap(min, i);
  }
  return *medLoc;
}

template <typename T>
auto partition(VIter<T> l, VIter<T> r, T P) {
  auto p = l;
  while (*p != P) ++p;  // find the pivot index
  assert(p != r);

  std::iter_swap(p, r - 1);  // move pivot to the end

  auto s = l;  // first not-smaller element
  for (auto i = l; i != r - 1; ++i) {
    if (*i < P) {
      std::iter_swap(i, s++);
    }
  }
  std::iter_swap(s, r - 1);
  return s;
}

template <typename T>
T protoSelect(VIter<T> l, VIter<T> r, int k) {
  assert(l + k < r);

  auto G = (r - l) / GROUPSIZE;
  if (l == r - 1 && k == 0 || G == 0) {
    return *(l + k);
  }

  auto M = std::vector<T>(G);
  for (auto g = 0; g < G; g++) {
    M[g] = medianOfGroup<T>(l + g * GROUPSIZE,
                            l + (g + 1) * GROUPSIZE);
  }  // O(n)

  auto P = protoSelect<T>(M.begin(), M.end(), G / 2);  // T(n / 5)

  auto s = partition<T>(l, r, P);  // O(n)

  if (l + k == s) {
    return *s;
  } else if (l + k < s) {
    return protoSelect<T>(l, s, k);
  } else {  // l + k > s
    return protoSelect<T>(s + 1, r, l + k - s - 1);
  }  // T(7n / 10)

  // T(n) = T(n / 5) + T(7n / 10) + O(n) = O(n)
}

template <typename T>
auto Select(VIter<T> l, VIter<T> r, int k) {
  auto B = std::vector<T>(l, r);
  return protoSelect<T>(B.begin(), B.end(), k);
}

int main() {
  auto A = std::vector<int>{12, 3, 2, 4, 9, 1, 5, 6, 8, 7, 10, 11};
  auto five = Select<int>(A.begin(), A.end(), 4);
  std::cout << five << std::endl;
}
