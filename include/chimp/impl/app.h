#ifndef CHIMP_IMPL_APP_H
#define CHIMP_IMPL_APP_H

#include "chimp/common.h"

#include "chimp/app.h"
#include "chimp/app_builder.h"

namespace chimp {

/** @param builder AppBuilder that is used to create App */
App::App(AppBuilder&& builder)
    : m_name{builder.m_name}
    , m_author{builder.m_author}
    , m_version{builder.m_version}
    , m_about{builder.m_about} {}

/** @param name Application's name */
AppBuilder App::builder(const std::string name) noexcept {
  return AppBuilder{name};
}

void App::parse(int argc, char** argv) {
  // parse CLI arguments
}

} // namespace chimp

#endif // CHIMP_IMPL_APP_H
