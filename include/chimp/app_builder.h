#ifndef CHIMP_APP_BUILDER_H
#define CHIMP_APP_BUILDER_H

#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

/**
 * Builder class for @ref App.
 */
class AppBuilder {
public:
  /** Constructs AppBuilder. */
  explicit AppBuilder(const std::string) noexcept;

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

private:
  /** @copydoc App::m_name */
  const std::string m_name;

  /** @copydoc App::m_author */
  std::optional<std::string> m_author;
  /** @copydoc App::m_version */
  std::optional<std::string> m_version;
  /** @copydoc App::m_about */
  std::optional<std::string> m_about;

  friend App;

#ifdef CHIMP_BUILD_TESTING
  friend testing::AppBuilderTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_APP_BUILDER_H
