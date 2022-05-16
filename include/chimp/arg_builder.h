#ifndef CHIMP_ARG_BUILDER_H
#define CHIMP_ARG_BUILDER_H

#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

class ArgBuilder {
public:
  ArgBuilder();

  ArgBuilder(const ArgBuilder&) = delete;
  explicit ArgBuilder(ArgBuilder&&) = default;
  ~ArgBuilder() = default;

  ArgBuilder& operator=(const ArgBuilder&) = delete;
  ArgBuilder& operator=(ArgBuilder&&) = default;

  ArgBuilder& short_name(const char) noexcept;
  ArgBuilder& long_name(const std::string) noexcept;

  Arg build();

private:
  std::optional<char> m_short;
  std::optional<std::string> m_long;

  friend Arg;

#ifdef CHIMP_BUILD_TESTING
  friend testing::ArgBuilderTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_ARG_BUILDER
