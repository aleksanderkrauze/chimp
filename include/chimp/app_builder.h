#ifndef CHIMP_APP_BUILDER_H
#define CHIMP_APP_BUILDER_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "chimp/common.h"

#include "chimp/arg.h"

namespace chimp {

/**
 * Builder class for @ref App.
 */
class CHIMP_EXPORT AppBuilder {
public:
  /**
   * Constructs AppBuilder.
   *
   * @invariant App's name must be non-empty. If it is empty this function will
   * throw LogicError.
   *
   * @throws LogicError
   */
  explicit AppBuilder(const std::string);

  AppBuilder(const AppBuilder&) = delete;
  explicit AppBuilder(AppBuilder&&) = default;
  ~AppBuilder() = default;

  AppBuilder& operator=(const AppBuilder&) = delete;
  AppBuilder& operator=(AppBuilder&&) = delete;

  /**
   * Creates and returns new @ref App.
   *
   * @warning This will move `*this` into App constructor.
   * Any later usage of AppBuilder object is an undefined behaviour.
   */
  App build();

  /** Sets application's author(s). */
  AppBuilder& author(const std::string) noexcept;
  /** Sets application's version. */
  AppBuilder& version(const std::string) noexcept;
  /** Sets application's about (a short text description displayed at the
   * beginning of a help screen).
   */
  AppBuilder& about(const std::string) noexcept;

  /**
   * Adds argument to App's argument list.
   *
   * @invariant Provided Arg must have unique short and long forms among all
   * previously added Args. It must also own some Arg and not be `nullptr`.
   * If any of this conditions is not true this function will throw
   * LogicError.
   *
   * @throws LogicError
   */
  AppBuilder& arg(const std::shared_ptr<Arg>&);

private:
  /** @copydoc App::m_name */
  const std::string m_name;

  /** @copydoc App::m_author */
  std::optional<std::string> m_author;
  /** @copydoc App::m_version */
  std::optional<std::string> m_version;
  /** @copydoc App::m_about */
  std::optional<std::string> m_about;

  /** @copydoc App::m_args */
  std::vector<std::shared_ptr<Arg>> m_args;

  friend App;

#ifdef CHIMP_BUILD_TESTING
  friend testing::AppBuilderTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_APP_BUILDER_H
