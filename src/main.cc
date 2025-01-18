#include "util.h"
#include <iostream>

int main(void) {
  nemus::range<int> a(0, 10);
  std::cout << a.contains(5) << std::endl;
  return 0;
}
