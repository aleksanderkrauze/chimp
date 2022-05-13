#ifndef CHIMP_APP_H
#define CHIMP_APP_H

#include "chimp/common.h"

namespace chimp {

/**
 * Main class used to parse command line arguments.
 * Prefered way to construct it is by using AppBuilder.
 */
class App {
public:
  App();
  App(AppBuilder&&);

  App(const App&) = delete;
  App(App&&) = default;
  App& operator=(const App&) = delete;
  App& operator=(App&&) = default;
  ~App() = default;

  static AppBuilder builder() noexcept;

  void parse(int, char**);

private:
  // members

#ifdef CHIMP_BUILD_TESTING
  friend testing::AppTest;
#endif // CHIMP_BUILD_TESTING
};

} // namespace chimp

#endif // CHIMP_APP_H
