#ifndef CHIMP_IMPL_ARG_H
#define CHIMP_IMPL_ARG_H

#include <utility>

#include "chimp/common.h"

#include "chimp/arg.h"
#include "chimp/arg_builder.h"
#include "chimp/exceptions.h"

namespace chimp {

/** @param builder ArgBuilder used to create Arg */
Arg::Arg(ArgBuilder&& builder)
    : m_name{std::move(builder.m_name)}
    , m_short{std::move(builder.m_short)}
    , m_long{std::move(builder.m_long)} {}

/**
 * @param name name of the argument. It is used to communicate errors to
 * developer/user not to match arguments on command line
 */
ArgBuilder Arg::builder(const std::string name) {
  return ArgBuilder{name};
}

const std::string& Arg::name() const noexcept {
  return this->m_name;
}

const std::optional<char>& Arg::short_arg() const noexcept {
  return this->m_short;
}

const std::optional<std::string>& Arg::long_arg() const noexcept {
  return this->m_long;
}

bool Arg::is_positional() const noexcept {
  return !(this->m_short.has_value() || this->m_long.has_value());
}

} // namespace chimp

#endif // CHIMP_IMPL_ARG_H
