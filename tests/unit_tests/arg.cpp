#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

using chimp::Arg;

const auto tester = chimp::testing::ArgTest();

TEST(Arg, member_variables_values_from_empty_builder) {
  const auto arg = Arg::builder("arg").build();

  // std::optionals are empty
  ASSERT_FALSE(tester.m_short(arg));
  ASSERT_FALSE(tester.m_long(arg));
}

TEST(Arg, member_variables_values_from_full_builder) {
  const auto arg =
    Arg::builder("arg").short_arg('p').long_arg("position").build();

  ASSERT_EQ(tester.m_short(arg).value(), 'p');
  ASSERT_STREQ(tester.m_long(arg).value().c_str(), "position");
}

TEST(Arg, bind) {
  std::shared_ptr<Arg> arg_ptr;

  std::shared_ptr<Arg> arg =
    Arg::builder("arg").short_arg('a').long_arg("all").build(arg_ptr);

  ASSERT_EQ(arg_ptr.get(), arg.get());
  ASSERT_TRUE(!(arg_ptr < arg || arg < arg_ptr));
}

TEST(Arg, bind_invariant_ptr_is_nullptr) {
  std::shared_ptr<Arg> arg_ptr;
  auto arg = Arg::builder("arg").build();

  // arg_ptr is empty so we can bind to it.
  ASSERT_NO_THROW(Arg::builder("arg").build(arg_ptr));

  // arg_ptr is no longer empty. Binding to it would be wrong.
  ASSERT_THROW(Arg::builder("arg").build(arg_ptr), chimp::LogicError);
}

TEST(Arg, is_positional) {
  const auto positional = Arg::builder("positional").build();
  const auto short_only = Arg::builder("short-only").short_arg('s').build();
  const auto long_only = Arg::builder("long-only").long_arg("long").build();
  const auto short_and_long =
    Arg::builder("short-and-long").short_arg('n').long_arg("num").build();

  ASSERT_TRUE(positional->is_positional());
  ASSERT_FALSE(short_only->is_positional());
  ASSERT_FALSE(long_only->is_positional());
  ASSERT_FALSE(short_and_long->is_positional());
}
