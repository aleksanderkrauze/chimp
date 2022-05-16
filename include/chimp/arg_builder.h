#ifndef CHIMP_ARG_BUILDER_H
#define CHIMP_ARG_BUILDER_H

#include "chimp/common.h"

namespace chimp {

class ArgBuilder {
public:
  //

private:
  friend Arg;

#ifdef CHIMP_BUILD_TESTING
  friend testing::ArgBuilderTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_ARG_BUILDER
