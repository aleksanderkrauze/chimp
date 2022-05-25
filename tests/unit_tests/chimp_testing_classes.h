#ifndef UNIT_TESTS_CHIMP_TESTING_CLASSES_H
#define UNIT_TESTS_CHIMP_TESTING_CLASSES_H

#include "chimp/chimp.h"

class chimp::testing::AppTest {
public:
  AppTest() = default;

  const std::string& m_name(const App& app) const noexcept {
    return app.m_name;
  }

  const std::optional<std::string>& m_author(const App& app) const noexcept {
    return app.m_author;
  }

  const std::optional<std::string>& m_version(const App& app) const noexcept {
    return app.m_version;
  }

  const std::optional<std::string>& m_about(const App& app) const noexcept {
    return app.m_about;
  }
};

class chimp::testing::AppBuilderTest {
public:
  AppBuilderTest() = default;

  const std::string& m_name(const AppBuilder& builder) const noexcept {
    return builder.m_name;
  }

  const std::optional<std::string>&
  m_author(const AppBuilder& builder) const noexcept {
    return builder.m_author;
  }

  const std::optional<std::string>&
  m_version(const AppBuilder& builder) const noexcept {
    return builder.m_version;
  }

  const std::optional<std::string>&
  m_about(const AppBuilder& builder) const noexcept {
    return builder.m_about;
  }

  const std::vector<std::shared_ptr<Arg>>&
  m_args(const AppBuilder& builder) const noexcept {
    return builder.m_args;
  }
};

class chimp::testing::ArgTest {
public:
  ArgTest() = default;

  const std::optional<char>&
  m_short(const std::shared_ptr<Arg>& arg) const noexcept {
    return arg->m_short;
  }

  const std::optional<std::string>&
  m_long(const std::shared_ptr<Arg>& arg) const noexcept {
    return arg->m_long;
  }

  const bool m_takes_value(const std::shared_ptr<Arg>& arg) const noexcept {
    return arg->m_takes_value;
  }

  const bool m_was_present(const std::shared_ptr<Arg>& arg) const noexcept {
    return arg->m_was_present;
  }
};

class chimp::testing::ArgBuilderTest {
public:
  ArgBuilderTest() = default;

  const std::string& m_name(const ArgBuilder& builder) const noexcept {
    return builder.m_name;
  }

  const std::optional<char>& m_short(const ArgBuilder& builder) const noexcept {
    return builder.m_short;
  }

  const std::optional<std::string>&
  m_long(const ArgBuilder& builder) const noexcept {
    return builder.m_long;
  }
};

#endif // UNIT_TESTS_CHIMP_TESTING_CLASSES_H
