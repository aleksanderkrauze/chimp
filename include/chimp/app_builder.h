#ifndef CHIMP_APP_BUILDER_H
#define CHIMP_APP_BUILDER_H

#include "chimp/common.h"

namespace chimp {

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
};

} // namespace chimp

#endif // CHIMP_APP_BUILDER_H
