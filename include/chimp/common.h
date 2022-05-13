#ifndef CHIMP_COMMON_H
#define CHIMP_COMMON_H

#include "chimp/cmake_config.h"

namespace chimp {

class App;
class AppBuilder;

namespace testing {

#ifdef CHIMP_BUILD_TESTING
  class AppTest;
  class AppBuilderTest;
#endif // CHIMP_BUILD_TESTING

} // namespace testing

} // namespace chimp

#endif // CHIMP_COMMON_H
