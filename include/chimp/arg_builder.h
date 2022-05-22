#ifndef CHIMP_ARG_BUILDER_H
#define CHIMP_ARG_BUILDER_H

#include <memory>
#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

/**
 * Builder class for @ref Arg.
 */
class ArgBuilder {
public:
  /**
   * Constructs ArgBuilder.
   *
   * @invariant Provided name must be non-empty. If it is empty this function
   * will throw a LogicError.
   *
   * @throws LogicError
   */
  CHIMP_EXPORT explicit ArgBuilder(const std::string);

  CHIMP_EXPORT ArgBuilder(const ArgBuilder&) = delete;
  CHIMP_EXPORT explicit ArgBuilder(ArgBuilder&&) = default;
  CHIMP_EXPORT ~ArgBuilder() = default;

  CHIMP_EXPORT ArgBuilder& operator=(const ArgBuilder&) = delete;
  CHIMP_EXPORT ArgBuilder& operator=(ArgBuilder&&) = default;

  /**
   * Creates and returns new @ref Arg wrapped in std::shared_ptr.
   *
   * @warning This will move `*this` into Arg constructor.
   * Any later usage of ArgBuilder object is an undefined behaviour.
   */
  CHIMP_EXPORT std::shared_ptr<Arg> build();

  /**
   * Creates and returns new @ref Arg wrapped in std::shared_ptr
   * and binds it to other shared pointer.
   *
   * @invariant Passed shared pointer must be empty (having value std::nullptr).
   * If not, then this function will throw @ref LogicError.
   *
   * @warning This will move `*this` into Arg constructor.
   * Any later usage of ArgBuilder object is an undefined behaviour.
   *
   * @throws LogicError
   */
  CHIMP_EXPORT std::shared_ptr<Arg> build(std::shared_ptr<Arg>&);

  /**
   * Sets Arg's short version.
   *
   * @invariant Provided value must be an **alphanumeric** character.
   * If it is violated this function will throw @ref LogicError.
   *
   * @throws LogicError
   */
  CHIMP_EXPORT ArgBuilder& short_arg(const char);
  /**
   * Sets Arg's long version.
   *
   * @invariant Provided value must have following properties:
   *   - Must be non empty
   *   - Must contain only alphanumeric characters and `-` (hyphen)
   *   - It cannot start with a `-`
   *
   * @invariant If it is violated this function will throw @ref LogicError.
   *
   * @throws LogicError
   */
  CHIMP_EXPORT ArgBuilder& long_arg(const std::string);

private:
  /** @copydoc Arg::m_name */
  std::string m_name;

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
