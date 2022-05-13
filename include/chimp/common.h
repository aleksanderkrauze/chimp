#ifndef CHIMP_COMMON_H
#define CHIMP_COMMON_H

#include "chimp/cmake_config.h"

namespace chimp {

class App;
class AppBuilder;

#ifdef CHIMP_BUILD_TESTING
namespace testing {

  class AppTest;
  class AppBuilderTest;

} // namespace testing
#endif // CHIMP_BUILD_TESTING

} // namespace chimp

#endif // CHIMP_COMMON_H
