#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

const auto tester = chimp::testing::ArgTest();

TEST(Arg, member_variables_values_from_empty_builder) {
  const auto arg = chimp::Arg::builder().build();

  // std::optionals are empty
  ASSERT_FALSE(tester.m_short(arg));
  ASSERT_FALSE(tester.m_long(arg));
}

TEST(Arg, member_variables_values_from_full_builder) {
  const auto arg =
    chimp::Arg::builder().short_name('p').long_name("position").build();

  ASSERT_EQ(tester.m_short(arg).value(), 'p');
  ASSERT_STREQ(tester.m_long(arg).value().c_str(), "position");
}
