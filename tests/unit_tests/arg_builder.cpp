#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

const auto tester = chimp::testing::ArgBuilderTest();

TEST(ArgBuilder, initial_member_variables_values) {
  const auto builder = chimp::ArgBuilder("arg");

  ASSERT_STREQ(tester.m_name(builder).c_str(), "arg");

  // std::optionals are empty
  ASSERT_FALSE(tester.m_short(builder));
  ASSERT_FALSE(tester.m_long(builder));
}

TEST(ArgBuilder, name_invariant_not_empty) {
  ASSERT_NO_THROW(chimp::ArgBuilder("non-empty"));
  ASSERT_THROW(chimp::ArgBuilder(""), chimp::LogicError);
}

TEST(ArgBuilder, short_arg) {
  auto builder = chimp::ArgBuilder("arg");
  ASSERT_FALSE(tester.m_short(builder));

  builder.short_arg('n');

  ASSERT_EQ(tester.m_short(builder).value(), 'n');
}

TEST(ArgBuilder, short_arg_invariant_alphanumerical) {
  auto builder = chimp::ArgBuilder("arg");

  ASSERT_NO_THROW(builder.short_arg('a'));
  ASSERT_NO_THROW(builder.short_arg('Z'));
  ASSERT_NO_THROW(builder.short_arg('0'));

  ASSERT_THROW(builder.short_arg(' '), chimp::LogicError);
  ASSERT_THROW(builder.short_arg('-'), chimp::LogicError);
  ASSERT_THROW(builder.short_arg('?'), chimp::LogicError);
  ASSERT_THROW(builder.short_arg('.'), chimp::LogicError);
  ASSERT_THROW(builder.short_arg(','), chimp::LogicError);
}

TEST(ArgBuilder, long_arg) {
  auto builder = chimp::ArgBuilder("arg");
  ASSERT_FALSE(tester.m_short(builder));

  builder.long_arg("name");

  ASSERT_STREQ(tester.m_long(builder).value().c_str(), "name");
}

TEST(ArgBuilder, long_arg_invariant_non_empty) {
  auto builder = chimp::ArgBuilder("arg");

  ASSERT_THROW(builder.long_arg(""), chimp::LogicError);
}

TEST(ArgBuilder, long_arg_invariant_alphanumerical_and_hyphen) {
  auto builder = chimp::ArgBuilder("arg");

  ASSERT_NO_THROW(builder.long_arg("two-words"));
  ASSERT_NO_THROW(builder.long_arg("4lph4-num3ric4l"));

  ASSERT_THROW(builder.long_arg("words with space"), chimp::LogicError);
  ASSERT_THROW(builder.long_arg("words_with_underscore"), chimp::LogicError);
  ASSERT_THROW(builder.long_arg("?!>"), chimp::LogicError);
}

TEST(ArgBuilder, long_arg_invariant_not_starting_with_hyphen) {
  auto builder = chimp::ArgBuilder("arg");

  ASSERT_NO_THROW(builder.long_arg("midd-le"));
  ASSERT_NO_THROW(builder.long_arg("end-"));

  ASSERT_THROW(builder.long_arg("-beginning"), chimp::LogicError);
}
