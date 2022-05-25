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
    , m_long{std::move(builder.m_long)}
    , m_takes_value{std::move(builder.m_takes_value)}
    , m_was_present{false} {}

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

void Arg::was_present(bool flag) noexcept {
  this->m_was_present = flag;
}

bool Arg::was_present() const noexcept {
  return this->m_was_present;
}

} // namespace chimp
