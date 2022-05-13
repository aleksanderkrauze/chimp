#ifndef CHIMP_APP_H
#define CHIMP_APP_H

#include <optional>
#include <string>

#include "chimp/common.h"

namespace chimp {

/**
 * Main class used to parse command line arguments.
 * Prefered way to construct it is by using AppBuilder.
 */
class App {
public:
  /**
   * Constructs %App from moved AppBuilder.
   */
  App(AppBuilder&&);

  App(const App&) = delete;
  App(App&&) = default;
  App& operator=(const App&) = delete;
  App& operator=(App&&) = delete;
  ~App() = default;

  /** Creates and returns new %AppBuilder. */
  static AppBuilder builder(const std::string) noexcept;

  void parse(int, char**);

private:
  /** Project's name. */
  const std::string m_name;

  /** Author(s) of a project. Will be displayed on help screen. */
  const std::optional<std::string> m_author;
  /** Project's version number. Will be displayed on help screen. */
  const std::optional<std::string> m_version;
  /** Project's short description.
   * Will be displayed at the begining of help screen.
   */
  const std::optional<std::string> m_about;

#ifdef CHIMP_BUILD_TESTING
  friend testing::AppTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_APP_H
