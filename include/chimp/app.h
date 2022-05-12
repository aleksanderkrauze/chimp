#ifndef CHIMP_APP_H
#define CHIMP_APP_H

#include "chimp/common.h"

namespace chimp {

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
};

} // namespace chimp

#endif // CHIMP_APP_H