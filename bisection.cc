#include <iostream>
constexpr int ARRAY_SIZE = 10;


int bisection(int *a, int n, int val) {
  // Return the index of val in a. If not found, return -1.

  // Convention of range: left-closed and right-open.
  int l = 0, r = n;

  // End condition: only one element in range a[l:r].
  while (l < r - 1) {
    // When the size is odd, a[l:m] is one element smaller than a[m:r].
    int m = (l + r) / 2;

    // CRITICAL POINT: always keep val in a[l:r].
    // Note that a[m] locates in a[m:r], so the condition should determine
    // whether val locates in a[m:r], too.
    if (a[m] <= val) {
      l = m;
    } else {
      r = m;
    }
  }

  // Finally, a[l:r] only has one element a[l].
  if (a[l] == val) {
    return l;
  } else {
    return -1;
  }
}


int main() {
  int a[ARRAY_SIZE] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
  std::cout << bisection(a, ARRAY_SIZE, 4) << std::endl;  // 2
  std::cout << bisection(a, ARRAY_SIZE, 128) << std::endl;  // 7
  std::cout << bisection(a, ARRAY_SIZE, 500) << std::endl;  // -1
}
