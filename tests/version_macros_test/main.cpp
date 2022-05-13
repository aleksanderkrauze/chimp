#include <iostream>

#include "chimp/chimp.h"

int main() {
  std::cout << chimp_VERSION_MAJOR << '.' << chimp_VERSION_MINOR << '.'
            << chimp_VERSION_PATCH << '\n';

  return 0;
}
