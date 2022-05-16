#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

const auto tester = chimp::testing::ArgBuilderTest();

TEST(ArgBuilder, initial_member_variables_values) {
  const auto builder = chimp::ArgBuilder();

  // std::optionals are empty
  ASSERT_FALSE(tester.m_short(builder));
  ASSERT_FALSE(tester.m_long(builder));
}

TEST(ArgBuilder, short_name) {
  auto builder = chimp::ArgBuilder();
  ASSERT_FALSE(tester.m_short(builder));

  builder.short_name('n');

  ASSERT_EQ(tester.m_short(builder).value(), 'n');
}

TEST(ArgBuilder, long_name) {
  auto builder = chimp::ArgBuilder();
  ASSERT_FALSE(tester.m_short(builder));

  builder.long_name("name");

  ASSERT_STREQ(tester.m_long(builder).value().c_str(), "name");
}
