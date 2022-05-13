#ifndef CHIMP_IMPL_APP_BUILDER_H
#define CHIMP_IMPL_APP_BUILDER_H

#include <utility>

#include "chimp/common.h"

#include "chimp/app.h"
#include "chimp/app_builder.h"

namespace chimp {

AppBuilder::AppBuilder() noexcept {}

App AppBuilder::build() { return App{std::move(*this)}; }

} // namespace chimp

#endif // CHIMP_IMPL_APP_BUILDER_H
