#include <cctype>
#include <utility>

#include "chimp/common.h"

#include "chimp/arg.h"
#include "chimp/arg_builder.h"
#include "chimp/errors.h"

namespace chimp {

/**
 * @param name name of the argument. It is used to communicate errors to
 * developer/user not to match arguments on command line
 */
ArgBuilder::ArgBuilder(const std::string name)
    : m_name{name.size() > 0 ? name
                             : throw LogicError{"Passed empty name to Arg"}}
    , m_short{std::nullopt}
    , m_long{std::nullopt}
    , m_takes_value{false} {}

std::shared_ptr<Arg> ArgBuilder::build() {
  // Positional arguments must take value
  if ((!this->m_short && !this->m_long) && !this->m_takes_value) {
    throw LogicError{"Cannot build positional argument `", this->m_name,
                     "` that has takes_value set to false"};
  }

  return std::make_shared<Arg>(Arg{std::move(*this)});
}

/** @param ptr Shared pointer to which we bind `*this` */
std::shared_ptr<Arg> ArgBuilder::build(std::shared_ptr<Arg>& ptr) {
  if (ptr) {
    throw LogicError{"Attempted to bind `", this->m_name,
                     "` Arg to a non empty shared pointer that is owning `",
                     ptr->m_name, "` Arg"};
  }

  // XXX: Do not use this after this line
  auto shared = this->build();

  ptr = shared;

  return shared;
}

/** @param arg Arg's short version */
ArgBuilder& ArgBuilder::short_arg(const char arg) {
  if (!std::isalnum(arg)) {
    throw LogicError{"Provided short argument `", arg, "` for `", this->m_name,
                     "` Arg is not alphanumeric"};
  }

  this->m_short = arg;
  return *this;
}

/** @param arg Arg's long version */
ArgBuilder& ArgBuilder::long_arg(const std::string arg) {
  if (arg.length() < 2) {
    throw LogicError{"Provided long argument for `", this->m_name,
                     "` Arg is shorter than 2 characters"};
  }
  if (arg[0] == '-') {
    throw LogicError{"Provided long argument `", arg, "` for `", this->m_name,
                     "` Arg begins with a hyphen"};
  }
  for (const auto& c : arg) {
    if (!isalnum(c) && !(c == '-')) {
      throw LogicError{"Provided long argument `",
                       arg,
                       "` for `",
                       this->m_name,
                       "` Arg contains an illegal character `",
                       c,
                       "`"};
    }
  }

  this->m_long = arg;
  return *this;
}

/** @param option true or false */
ArgBuilder& ArgBuilder::takes_value(const bool option) {
  this->m_takes_value = option;
  return *this;
}

} // namespace chimp
