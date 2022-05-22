#ifndef CHIMP_APP_H
#define CHIMP_APP_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "chimp/common.h"

#include "chimp/arg.h"

namespace chimp {

/**
 * Main class used to parse command line arguments.
 * Preferred way to construct it is by using AppBuilder (see below).
 *
 * ```
 * auto app = App::builder("Awesome app")
 *                .author("Great developer")
 *                .version("1.0.0")
 *                .about("This app allows to do awesome things")
 *                .build();
 * ```
 *
 * @see @ref AppBuilder
 */
class App {
public:
  /** Constructs App from moved @ref AppBuilder. */
  CHIMP_EXPORT explicit App(AppBuilder&&);

  CHIMP_EXPORT App(const App&) = delete;
  CHIMP_EXPORT explicit App(App&&) = default;
  CHIMP_EXPORT ~App() = default;

  CHIMP_EXPORT App& operator=(const App&) = delete;
  CHIMP_EXPORT App& operator=(App&&) = delete;

  /**
   * Creates and returns new AppBuilder.
   *
   * @invariant App's name must be non-empty. If it is empty this function will
   * throw LogicError.
   *
   * @throws LogicError
   */
  CHIMP_EXPORT static AppBuilder builder(const std::string) noexcept;

  CHIMP_EXPORT void parse(int, char**);

private:
  /** Project's name. */
  const std::string m_name;

  /** Author(s) of a project. Will be displayed on help screen. */
  const std::optional<std::string> m_author;
  /** Project's version number. Will be displayed on help screen. */
  const std::optional<std::string> m_version;
  /** Project's short description.
   * Will be displayed at the beginning of help screen.
   */
  const std::optional<std::string> m_about;

  /** App's arguments */
  std::vector<std::shared_ptr<Arg>> m_args;

#ifdef CHIMP_BUILD_TESTING
  friend testing::AppTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_APP_H
