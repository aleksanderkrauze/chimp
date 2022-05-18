#ifndef CHIMP_IMPL_APP_BUILDER_H
#define CHIMP_IMPL_APP_BUILDER_H

#include <utility>

#include "chimp/common.h"

#include "chimp/app.h"
#include "chimp/app_builder.h"

namespace chimp {

/** @param name Application's name */
AppBuilder::AppBuilder(const std::string name) noexcept
    : m_name{name}
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
AppBuilder& AppBuilder::arg(const std::shared_ptr<Arg>& arg) noexcept {
  this->m_args.push_back(arg);
  return *this;
}

} // namespace chimp

#endif // CHIMP_IMPL_APP_BUILDER_H
