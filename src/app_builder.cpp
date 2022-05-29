#include <sstream>
#include <utility>

#include "chimp/common.h"

#include "chimp/app.h"
#include "chimp/app_builder.h"
#include "chimp/errors.h"

namespace chimp {

/** @param name Application's name */
AppBuilder::AppBuilder(const std::string name)
    : m_name{name.size() > 0 ? name
                             : throw LogicError{"Passed empty name to App"}}
    , m_author{std::nullopt}
    , m_version{std::nullopt}
    , m_about{std::nullopt} {}

App AppBuilder::build() {
  return App{std::move(*this)};
}

/** @param author application's author */
AppBuilder& AppBuilder::author(const std::string author) noexcept {
  this->m_author = author;
  return *this;
}

/** @param version application's version */
AppBuilder& AppBuilder::version(const std::string version) noexcept {
  this->m_version = version;
  return *this;
}

/** @param about applications short text description */
AppBuilder& AppBuilder::about(const std::string about) noexcept {
  this->m_about = about;
  return *this;
}

/** @param arg Arg added to app's argument list */
AppBuilder& AppBuilder::arg(const std::shared_ptr<Arg>& arg) {
  if (!arg) {
    throw LogicError{"Passed nullptr shared pointer to AppBuilder::arg"};
  }

  const auto conflicting = [](const auto& x, const auto& y) -> bool {
    if (x && y) {
      return x.value() == y.value();
    }

    return false;
  };
  for (const auto& a : this->m_args) {
    if (conflicting(a->short_arg(), arg->short_arg()) ||
        conflicting(a->long_arg(), arg->long_arg())) {
      throw LogicError{"Cannot add `", arg->name(),
                       "` Arg to App as it is conflicting with `", a->name(),
                       "` Arg"};
    }
  }

  this->m_args.push_back(arg);
  return *this;
}

} // namespace chimp
