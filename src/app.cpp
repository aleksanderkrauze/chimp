#include <utility>

#include "chimp/common.h"

#include "chimp/app.h"
#include "chimp/app_builder.h"

namespace chimp {

/** @param builder AppBuilder that is used to create App */
App::App(AppBuilder&& builder)
    : m_name{std::move(builder.m_name)}
    , m_author{std::move(builder.m_author)}
    , m_version{std::move(builder.m_version)}
    , m_about{std::move(builder.m_about)}
    , m_args{std::move(builder.m_args)} {}

/** @param name Application's name */
AppBuilder App::builder(const std::string name) noexcept {
  return AppBuilder{name};
}

void App::parse(int argc, char** argv) {
  // parse CLI arguments
}

} // namespace chimp
