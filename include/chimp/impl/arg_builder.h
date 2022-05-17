#ifndef CHIMP_IMPL_ARG_BUILDER_H
#define CHIMP_IMPL_ARG_BUILDER_H

#include <utility>

#include "chimp/common.h"

#include "chimp/arg.h"
#include "chimp/arg_builder.h"

namespace chimp {

ArgBuilder::ArgBuilder()
    : m_short{std::nullopt}
    , m_long{std::nullopt} {}

// TODO: Validate passed name
/** @param arg Arg's short version */
ArgBuilder& ArgBuilder::short_arg(const char arg) noexcept {
  this->m_short = arg;
  return *this;
}

// TODO: Validate passed name
/** @param arg Arg's long version */
ArgBuilder& ArgBuilder::long_arg(const std::string arg) noexcept {
  this->m_long = arg;
  return *this;
}

Arg ArgBuilder::build() {
  return Arg{std::move(*this)};
}

} // namespace chimp

#endif // CHIMP_IMPL_ARG_BUILDER_H
