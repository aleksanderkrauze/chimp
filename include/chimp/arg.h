#ifndef CHIMP_ARG_H
#define CHIMP_ARG_H

#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

/**
 * Representation of an argument passed through command line.
 *
 * Preferred way to create it is by using ArgBuilder (see example below)
 *
 * ```
 * auto arg = Arg::builder()
 *                .short_arg('n')
 *                .long_arg("name")
 *                .build();
 * ```
 *
 * @see @ref ArgBuilder
 */
class Arg {
public:
  /** Constructs Arg from moved @ref ArgBuilder. */
  explicit Arg(ArgBuilder&&);

  Arg(const Arg&) = delete;
  explicit Arg(Arg&&) = default;
  ~Arg() = default;

  Arg& operator=(const Arg&) = delete;
  Arg& operator=(Arg&&) = delete;

  /** Creates and returns new ArgBuilder */
  static ArgBuilder builder() noexcept;

private:
  /**
   * Argument's short form.
   *
   * When for example set to `n` will match `-n` on command line.
   */
  const std::optional<char> m_short;
  /**
   * Argument's long form.
   *
   * When for example set to `number` will match `--number` on command line.
   */
  const std::optional<std::string> m_long;

#ifdef CHIMP_BUILD_TESTING
  friend testing::ArgTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_ARG_H
