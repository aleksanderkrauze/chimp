#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

using chimp::Arg;

const auto tester = chimp::testing::ArgTest();

TEST(Arg, member_variables_values_from_empty_builder) {
  const auto arg = Arg::builder().build();

  // std::optionals are empty
  ASSERT_FALSE(tester.m_short(arg));
  ASSERT_FALSE(tester.m_long(arg));
}

TEST(Arg, member_variables_values_from_full_builder) {
  const auto arg = Arg::builder().short_arg('p').long_arg("position").build();

  ASSERT_EQ(tester.m_short(arg).value(), 'p');
  ASSERT_STREQ(tester.m_long(arg).value().c_str(), "position");
}

TEST(Arg, is_positional) {
  const auto positional = Arg::builder().build();
  const auto short_only = Arg::builder().short_arg('s').build();
  const auto long_only = Arg::builder().long_arg("long").build();
  const auto short_and_long =
    Arg::builder().short_arg('n').long_arg("num").build();

  ASSERT_TRUE(positional.is_positional());
  ASSERT_FALSE(short_only.is_positional());
  ASSERT_FALSE(long_only.is_positional());
  ASSERT_FALSE(short_and_long.is_positional());
}
