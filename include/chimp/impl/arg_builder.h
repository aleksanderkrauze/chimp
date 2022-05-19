#ifndef CHIMP_IMPL_ARG_BUILDER_H
#define CHIMP_IMPL_ARG_BUILDER_H

#include <cctype>
#include <sstream>
#include <utility>

#include "chimp/common.h"

#include "chimp/arg.h"
#include "chimp/arg_builder.h"
#include "chimp/exceptions.h"

namespace chimp {

/**
 * @param name name of the argument. It is used to communicate errors to
 * developer/user not to match arguments on command line
 */
ArgBuilder::ArgBuilder(const std::string name)
    : m_name{name.size() > 0 ? name
                             : throw LogicError{"Passed empty name to Arg"}}
    , m_short{std::nullopt}
    , m_long{std::nullopt} {}

std::shared_ptr<Arg> ArgBuilder::build() {
  return std::make_shared<Arg>(Arg{std::move(*this)});
}

/** @param ptr Shared pointer to which we bind `*this` */
std::shared_ptr<Arg> ArgBuilder::build(std::shared_ptr<Arg>& ptr) {
  if (ptr) {
    std::ostringstream ss;
    ss << "Attempted to bind `" << this->m_name
       << "` Arg to a non empty shared pointer that is owning `" << ptr->m_name
       << "` Arg";

    throw LogicError{ss.str()};
  }

  // XXX: Do not use this after this line
  auto shared = this->build();

  ptr = shared;

  return shared;
}

/** @param arg Arg's short version */
ArgBuilder& ArgBuilder::short_arg(const char arg) {
  if (!std::isalnum(arg)) {
    std::ostringstream ss;
    ss << "Provided short argument `" << arg << "` for `" << this->m_name
       << "` Arg is not alphanumeric";

    throw LogicError{ss.str()};
  }

  this->m_short = arg;
  return *this;
}

/** @param arg Arg's long version */
ArgBuilder& ArgBuilder::long_arg(const std::string arg) {
  if (arg.length() == 0) {
    std::ostringstream ss;
    ss << "Provided empty long argument for `" << this->m_name << "` Arg";

    throw LogicError{ss.str()};
  }
  if (arg[0] == '-') {
    std::ostringstream ss;
    ss << "Provided long argument `" << arg << "` for `" << this->m_name
       << "` Arg begins with a hyphen";

    throw LogicError{ss.str()};
  }
  for (const auto& c : arg) {
    if (!isalnum(c) && !(c == '-')) {
      std::ostringstream ss;
      ss << "Provided long argument `" << arg << "` for `" << this->m_name
         << "` Arg contains an illegal character";

      throw LogicError{ss.str()};
    }
  }

  this->m_long = arg;
  return *this;
}

} // namespace chimp

#endif // CHIMP_IMPL_ARG_BUILDER_H
