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
class CHIMP_EXPORT ArgBuilder {
public:
  /**
   * Constructs ArgBuilder.
   *
   * @invariant Provided name must be non-empty. If it is empty this function
   * will throw a LogicError.
   *
   * @throws LogicError
   */
  explicit ArgBuilder(const std::string);

  ArgBuilder(const ArgBuilder&) = delete;
  explicit ArgBuilder(ArgBuilder&&) = default;
  ~ArgBuilder() = default;

  ArgBuilder& operator=(const ArgBuilder&) = delete;
  ArgBuilder& operator=(ArgBuilder&&) = default;

  /**
   * Creates and returns new @ref Arg wrapped in std::shared_ptr.
   *
   * @invariant If Arg is positional (doesn't have set either short or long arg
   * form) it must take value. If not this function will throw @ref LogicError.
   *
   * @warning This will move `*this` into Arg constructor.
   * Any later usage of ArgBuilder object is an undefined behaviour.
   *
   * @throws LogicError
   */
  std::shared_ptr<Arg> build();

  /**
   * Creates and returns new @ref Arg wrapped in std::shared_ptr
   * and binds it to other shared pointer.
   *
   * In addition to following invariants all invariants from other overload of
   * this function must be upheld.
   *
   * @invariant Passed shared pointer must be empty (having value std::nullptr).
   * If not, then this function will throw @ref LogicError.
   *
   * @warning This will move `*this` into Arg constructor.
   * Any later usage of ArgBuilder object is an undefined behaviour.
   *
   * @throws LogicError
   */
  std::shared_ptr<Arg> build(std::shared_ptr<Arg>&);

  /**
   * Sets Arg's short version.
   *
   * @invariant Provided value must be an **alphanumeric** character.
   * If it is violated this function will throw @ref LogicError.
   *
   * @throws LogicError
   */
  ArgBuilder& short_arg(const char);
  /**
   * Sets Arg's long version.
   *
   * @invariant Provided value must have following properties:
   *   - Must be at least 2 characters long
   *   - Must contain only alphanumeric characters and `-` (hyphen)
   *   - It cannot start with a `-`
   *
   * @invariant If it is violated this function will throw @ref LogicError.
   *
   * @throws LogicError
   */
  ArgBuilder& long_arg(const std::string);

  /**
   * If passed value is `true` then Arg constructed from this builder will take
   * value.
   *
   * Default value for *takes_value* for new ArgBuilder is `false`. Set this to
   * true if you want to not only check if some flag was present on command line
   * but if you also want to pass with it some information. It **must** be set
   * to `true` for positional arguments.
   */
  ArgBuilder& takes_value(const bool);

private:
  /** @copydoc Arg::m_name */
  std::string m_name;

  /** @copydoc Arg::m_short */
  std::optional<char> m_short;
  /** @copydoc Arg::m_long */
  std::optional<std::string> m_long;
  /** @copydoc Arg::m_takes_value */
  bool m_takes_value;

  friend Arg;

#ifdef CHIMP_BUILD_TESTING
  friend testing::ArgBuilderTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_ARG_BUILDER
