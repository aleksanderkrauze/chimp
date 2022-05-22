#ifndef CHIMP_ARG_H
#define CHIMP_ARG_H

#include <memory>
#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

/**
 * Representation of an argument passed through command line.
 *
 * Arguments can be either named or positional. They are named when they have
 * at least one of short and long format defined. And positional otherwise.
 * Named arguments are matched on command line by using their short or long
 * format. Positional on the other hand are matched according to their relative
 * position to each other.
 *
 * ```
 * // This shared pointer initially does not own any Arg
 * std::shared_ptr<Arg> arg_ptr;
 *
 * auto arg = Arg::builder("name")
 *                .short_arg('n')
 *                .long_arg("name")
 *                .build(arg_ptr)
 *
 * // Now we can move arg into an App and safely refer to it through arg_ptr
 * ```
 *
 * @see @ref ArgBuilder
 */
class Arg {
public:
  /** Constructs Arg from moved @ref ArgBuilder. */
  CHIMP_EXPORT explicit Arg(ArgBuilder&&);

  CHIMP_EXPORT Arg(const Arg&) = delete;
  CHIMP_EXPORT explicit Arg(Arg&&) = default;
  CHIMP_EXPORT ~Arg() = default;

  CHIMP_EXPORT Arg& operator=(const Arg&) = delete;
  CHIMP_EXPORT Arg& operator=(Arg&&) = delete;

  /**
   * Creates and returns new ArgBuilder
   *
   * @invariant Provided name must be non-empty. If it is empty this function
   * will throw a LogicError.
   *
   * @throws LogicError
   */
  CHIMP_EXPORT static ArgBuilder builder(const std::string);

  /** Returns Arg's name */
  CHIMP_EXPORT const std::string& name() const noexcept;

  /** Returns Arg's short format */
  CHIMP_EXPORT const std::optional<char>& short_arg() const noexcept;

  /** Returns Arg's long format */
  CHIMP_EXPORT const std::optional<std::string>& long_arg() const noexcept;

  /** Returns `true` when Arg is a positional argument. */
  CHIMP_EXPORT bool is_positional() const noexcept;

private:
  /**
   * Argument's name.
   *
   * It is not used to match on command line, but to differentiate
   * between args when reporting errors (for developer or user).
   */
  const std::string m_name;
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

  friend ArgBuilder;

#ifdef CHIMP_BUILD_TESTING
  friend testing::ArgTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_ARG_H
