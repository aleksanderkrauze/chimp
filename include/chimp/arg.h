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
 * The only way to create it is by using ArgBuilder (see example below) as this
 * class does not have any public constructors. Thanks to that it can safely
 * inherit from `std::enable_shared_from_this<Arg>` and that allows to safely
 * "bind" (see @ref Arg::bind) itself to another shared pointer from inside
 * providing clean API.
 *
 * ```
 * // This shared pointer initially does not own any Arg
 * std::shared_ptr<Arg> arg_ptr;
 *
 * auto arg = Arg::builder()
 *                .short_arg('n')
 *                .long_arg("name")
 *                .build() // This returns std::shared_ptr<Arg>
 *               ->bind(arg_ptr); // We bind this to arg_ptr
 *
 * // Now we can move arg into an App and safely refer to it through arg_ptr
 * ```
 *
 * @see @ref ArgBuilder
 */
class Arg : public std::enable_shared_from_this<Arg> {
public:
  Arg(const Arg&) = delete;
  explicit Arg(Arg&&) = default;
  ~Arg() = default;

  Arg& operator=(const Arg&) = delete;
  Arg& operator=(Arg&&) = delete;

  /** Creates and returns new ArgBuilder */
  static ArgBuilder builder() noexcept;

  /**
   * Binds `this` to another `std::shared_ptr<Arg>`
   *
   * `this` is owned by some `std::shared_ptr<Arg>`. By calling this
   * function and passing to it another **empty** shared pointer we
   * "bind" them together, meaning that they both point now to `this`
   * and have the same shared ownership of it.
   *
   * @returns This function returns `std::shared_ptr<Arg>` to allow chaining
   * this function with @ref ArgBuilder::build.
   *
   * @invariant Passed shared pointer must be empty (having value std::nullptr).
   * If not, then this function will throw @ref LogicError.
   *
   * @par
   * @invariant `this` must be owned by a `std::shared_ptr`.
   * This invariant is always upheld, because Arg has no public constructors
   * and the only way to create it is by calling @ref ArgBuilder::build.
   */
  std::shared_ptr<Arg> bind(std::shared_ptr<Arg>&);

  /** Returns `true` when Arg is a positional argument. */
  bool is_positional() const noexcept;

private:
  /** Constructs Arg from moved @ref ArgBuilder. */
  explicit Arg(ArgBuilder&&);

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
