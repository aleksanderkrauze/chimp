#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

using chimp::Arg;

const auto tester = chimp::testing::ArgTest();

TEST(Arg, member_variables_values_from_empty_builder) {
  const auto arg = Arg::builder("arg").takes_value(true).build();

  // std::optionals are empty
  ASSERT_FALSE(tester.m_short(arg));
  ASSERT_FALSE(tester.m_long(arg));

  ASSERT_TRUE(tester.m_takes_value(arg));
}

TEST(Arg, member_variables_values_from_full_builder) {
  const auto arg = Arg::builder("arg")
                     .short_arg('p')
                     .long_arg("position")
                     .takes_value(false)
                     .build();

  ASSERT_EQ(tester.m_short(arg).value(), 'p');
  ASSERT_STREQ(tester.m_long(arg).value().c_str(), "position");

  ASSERT_FALSE(tester.m_takes_value(arg));
}

TEST(Arg, name) {
  const auto arg = Arg::builder("arg").takes_value(true).build();

  ASSERT_STREQ(arg->name().c_str(), "arg");
}

TEST(Arg, short_arg) {
  const auto arg1 = Arg::builder("arg").takes_value(true).build();
  ASSERT_FALSE(arg1->short_arg());

  const auto arg2 = Arg::builder("arg").short_arg('x').build();
  ASSERT_EQ(arg2->short_arg().value(), 'x');
}

TEST(Arg, long_arg) {
  const auto arg1 = Arg::builder("arg").takes_value(true).build();
  ASSERT_FALSE(arg1->long_arg());

  const auto arg2 = Arg::builder("arg").long_arg("long").build();
  ASSERT_STREQ(arg2->long_arg().value().c_str(), "long");
}

TEST(Arg, is_positional) {
  const auto positional = Arg::builder("positional").takes_value(true).build();
  const auto short_only = Arg::builder("short-only").short_arg('s').build();
  const auto long_only = Arg::builder("long-only").long_arg("long").build();
  const auto short_and_long =
    Arg::builder("short-and-long").short_arg('n').long_arg("num").build();

  ASSERT_TRUE(positional->is_positional());
  ASSERT_FALSE(short_only->is_positional());
  ASSERT_FALSE(long_only->is_positional());
  ASSERT_FALSE(short_and_long->is_positional());
}

TEST(Arg, positional_args_take_vale) {
  const auto positional = Arg::builder("positional").takes_value(true).build();
  const auto short_only = Arg::builder("short-only").short_arg('s').build();
  const auto long_only = Arg::builder("long-only").long_arg("long").build();
  const auto short_and_long =
    Arg::builder("short-and-long").short_arg('n').long_arg("num").build();

  ASSERT_TRUE(tester.m_takes_value(positional));

  ASSERT_FALSE(tester.m_takes_value(short_only));
  ASSERT_FALSE(tester.m_takes_value(long_only));
  ASSERT_FALSE(tester.m_takes_value(short_and_long));
}

TEST(Arg, not_positional_takes_value) {
  const auto arg =
    Arg::builder("flag").short_arg('f').takes_value(true).build();

  ASSERT_TRUE(tester.m_takes_value(arg));
}
