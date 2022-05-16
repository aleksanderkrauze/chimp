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
};

class chimp::testing::ArgTest {
public:
  ArgTest() = default;
};

class chimp::testing::ArgBuilderTest {
public:
  ArgBuilderTest() = default;
};

#endif // UNIT_TESTS_CHIMP_TESTING_CLASSES_H
