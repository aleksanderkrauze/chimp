#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

const auto tester = chimp::testing::AppBuilderTest();

TEST(AppBuilder, initial_member_variables_values) {
  const auto app_builder = chimp::AppBuilder("test");

  ASSERT_STREQ(tester.m_name(app_builder).c_str(), "test");

  // std::optionals are empty
  ASSERT_FALSE(tester.m_author(app_builder));
  ASSERT_FALSE(tester.m_version(app_builder));
  ASSERT_FALSE(tester.m_about(app_builder));
}

TEST(AppBuilder, author) {
  auto app_builder = chimp::AppBuilder("test");
  ASSERT_FALSE(tester.m_author(app_builder));

  app_builder.author("Some author");
  const auto m_author = tester.m_author(app_builder);

  ASSERT_STREQ(m_author.value().c_str(), "Some author");
}

TEST(AppBuilder, version) {
  auto app_builder = chimp::AppBuilder("test");
  ASSERT_FALSE(tester.m_version(app_builder));

  app_builder.version("1.2.3");
  const auto m_version = tester.m_version(app_builder);

  ASSERT_STREQ(m_version.value().c_str(), "1.2.3");
}

TEST(AppBuilder, about) {
  auto app_builder = chimp::AppBuilder("test");
  ASSERT_FALSE(tester.m_about(app_builder));

  app_builder.about("Short description of a program");
  const auto m_about = tester.m_about(app_builder);

  ASSERT_STREQ(m_about.value().c_str(), "Short description of a program");
}
