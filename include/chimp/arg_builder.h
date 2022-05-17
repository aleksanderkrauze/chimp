#ifndef CHIMP_ARG_BUILDER_H
#define CHIMP_ARG_BUILDER_H

#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

/**
 * Builder class for @ref Arg.
 */
class ArgBuilder {
public:
  /** Constructs ArgBuilder. */
  ArgBuilder();

  ArgBuilder(const ArgBuilder&) = delete;
  explicit ArgBuilder(ArgBuilder&&) = default;
  ~ArgBuilder() = default;

  ArgBuilder& operator=(const ArgBuilder&) = delete;
  ArgBuilder& operator=(ArgBuilder&&) = default;

  /**
   * Creates and returns new @ref Arg.
   *
   * @warning This will move `*this` into Arg constructor.
   * Any later usage of ArgBuilder object is an undefined behaviour.
   */
  Arg build();

  /**
   * Sets Arg's short version.
   *
   * @invariant Provided value must be an **alphanumeric** character.
   * If it is violated this function will throw @ref LogicError.
   */
  ArgBuilder& short_arg(const char);
  /**
   * Sets Arg's long version.
   *
   * @invariant Provided value must have following properties:
   *   - Must be non empty
   *   - Must contain only alphanumeric characters and `-` (hyphen)
   *   - It cannot start with a `-`
   *
   * @invariant If it is violated this function will throw @ref LogicError.
   */
  ArgBuilder& long_arg(const std::string);

private:
  /** @copydoc Arg::m_short */
  std::optional<char> m_short;
  /** @copydoc Arg::m_long */
  std::optional<std::string> m_long;

  friend Arg;

#ifdef CHIMP_BUILD_TESTING
  friend testing::ArgBuilderTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_ARG_BUILDER
