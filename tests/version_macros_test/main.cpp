#include <iostream>

#include "chimp/chimp.h"

int main() {
  std::cout << CHIMP_VERSION_MAJOR << '.' << CHIMP_VERSION_MINOR << '.'
            << CHIMP_VERSION_PATCH << '\n';

  return 0;
}
