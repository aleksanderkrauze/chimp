#ifndef CHIMP_IMPL_ARG_H
#define CHIMP_IMPL_ARG_H

#include "chimp/common.h"

#include "chimp/arg.h"
#include "chimp/arg_builder.h"

namespace chimp {

Arg::Arg(ArgBuilder&& builder)
    : m_short{builder.m_short}
    , m_long{builder.m_long} {}

ArgBuilder Arg::builder() noexcept {
  return ArgBuilder{};
}

} // namespace chimp

#endif // CHIMP_IMPL_ARG_H
