#ifndef CHIMP_ARG_H
#define CHIMP_ARG_H

#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

class Arg {
public:
  explicit Arg(ArgBuilder&&);

  Arg(const Arg&) = delete;
  Arg& operator=(const Arg&) = delete;
  explicit Arg(Arg&&) = default;
  Arg& operator=(Arg&&) = delete;
  ~Arg() = default;

  static ArgBuilder builder() noexcept;

private:
  const std::optional<char> m_short;
  const std::optional<std::string> m_long;

#ifdef CHIMP_BUILD_TESTING
  friend testing::ArgTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_ARG_H
