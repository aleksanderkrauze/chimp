#ifndef CHIMP_IMPL_APP_H
#define CHIMP_IMPL_APP_H

#include "chimp/common.h"

#include "chimp/app.h"
#include "chimp/app_builder.h"

namespace chimp {

App::App() {}

App::App(AppBuilder&& builder) : App{} {}

AppBuilder App::builder() noexcept { return AppBuilder{}; }

void App::parse(int argc, char** argv) {
  // parse CLI arguments
}

} // namespace chimp

#endif // CHIMP_IMPL_APP_H