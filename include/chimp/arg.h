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
  explicit Arg(Arg&&) = default;
  ~Arg() = default;

  Arg& operator=(const Arg&) = delete;
  Arg& operator=(Arg&&) = delete;

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
