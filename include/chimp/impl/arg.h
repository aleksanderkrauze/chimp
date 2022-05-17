#ifndef CHIMP_IMPL_ARG_H
#define CHIMP_IMPL_ARG_H

#include "chimp/common.h"

#include "chimp/arg.h"
#include "chimp/arg_builder.h"

namespace chimp {

/** @param builder ArgBuilder used to create Arg */
Arg::Arg(ArgBuilder&& builder)
    : m_short{builder.m_short}
    , m_long{builder.m_long} {}

bool Arg::is_positional() const noexcept {
  return !(this->m_short.has_value() || this->m_long.has_value());
}

ArgBuilder Arg::builder() noexcept {
  return ArgBuilder{};
}

} // namespace chimp

#endif // CHIMP_IMPL_ARG_H
