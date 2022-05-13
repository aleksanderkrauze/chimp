#ifndef CHIMP_APP_BUILDER_H
#define CHIMP_APP_BUILDER_H

#include "chimp/common.h"

namespace chimp {

/**
 * Builder class for App.
 */
class AppBuilder {
public:
  AppBuilder() noexcept;

  AppBuilder(const AppBuilder&) = delete;
  AppBuilder(AppBuilder&&) = default;
  AppBuilder& operator=(const AppBuilder&) = delete;
  AppBuilder& operator=(AppBuilder&&) = default;
  ~AppBuilder() = default;

  App build();

private:
  // members

#ifdef CHIMP_BUILD_TESTING
  friend testing::AppBuilderTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_APP_BUILDER_H
