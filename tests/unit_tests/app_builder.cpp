#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

const auto tester = chimp::testing::AppBuilderTest();

TEST(AppBuilder, initial_member_variables_values) {
  const auto builder = chimp::AppBuilder("test");

  ASSERT_STREQ(tester.m_name(builder).c_str(), "test");

  // std::optionals are empty
  ASSERT_FALSE(tester.m_author(builder));
  ASSERT_FALSE(tester.m_version(builder));
  ASSERT_FALSE(tester.m_about(builder));
}

TEST(AppBuilder, author) {
  auto builder = chimp::AppBuilder("test");
  ASSERT_FALSE(tester.m_author(builder));

  builder.author("Some author");

  ASSERT_STREQ(tester.m_author(builder).value().c_str(), "Some author");
}

TEST(AppBuilder, version) {
  auto builder = chimp::AppBuilder("test");
  ASSERT_FALSE(tester.m_version(builder));

  builder.version("1.2.3");

  ASSERT_STREQ(tester.m_version(builder).value().c_str(), "1.2.3");
}

TEST(AppBuilder, about) {
  auto builder = chimp::AppBuilder("test");
  ASSERT_FALSE(tester.m_about(builder));

  builder.about("Short description of a program");

  ASSERT_STREQ(tester.m_about(builder).value().c_str(),
               "Short description of a program");
}
