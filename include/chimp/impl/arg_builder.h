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
ArgBuilder& ArgBuilder::short_name(const char name) noexcept {
  this->m_short = name;
  return *this;
}

// TODO: Validate passed name
ArgBuilder& ArgBuilder::long_name(const std::string name) noexcept {
  this->m_long = name;
  return *this;
}

Arg ArgBuilder::build() {
  return Arg{std::move(*this)};
}

} // namespace chimp

#endif // CHIMP_IMPL_ARG_BUILDER_H
