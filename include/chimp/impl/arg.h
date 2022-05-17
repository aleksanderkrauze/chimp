#ifndef CHIMP_IMPL_ARG_H
#define CHIMP_IMPL_ARG_H

#include "chimp/common.h"

#include "chimp/arg.h"
#include "chimp/arg_builder.h"
#include "chimp/exceptions.h"

namespace chimp {

/** @param builder ArgBuilder used to create Arg */
Arg::Arg(ArgBuilder&& builder)
    : m_short{builder.m_short}
    , m_long{builder.m_long} {}

ArgBuilder Arg::builder() noexcept {
  return ArgBuilder{};
}

/** @param ptr Shared pointer to which we bind `this` */
std::shared_ptr<Arg> Arg::bind(std::shared_ptr<Arg>& ptr) {
  if (ptr) {
    throw LogicError{"Attempted to bind Arg to a non empty shared pointer"};
  }

  ptr = this->shared_from_this();

  return this->shared_from_this();
}

bool Arg::is_positional() const noexcept {
  return !(this->m_short.has_value() || this->m_long.has_value());
}

} // namespace chimp

#endif // CHIMP_IMPL_ARG_H
