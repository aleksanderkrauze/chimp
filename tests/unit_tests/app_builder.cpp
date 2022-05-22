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

TEST(AppBuilder, name_invariant_non_empty) {
  ASSERT_NO_THROW(chimp::AppBuilder("non-empty"));
  ASSERT_THROW(chimp::AppBuilder(""), chimp::LogicError);
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

TEST(AppBuilder, arg) {
  std::shared_ptr<chimp::Arg> first, second;

  chimp::AppBuilder builder = chimp::AppBuilder("test");
  builder.arg(chimp::ArgBuilder("first").short_arg('f').build(first));
  builder.arg(chimp::ArgBuilder("second").long_arg("second").build(second));

  const auto& args = tester.m_args(builder);

  ASSERT_EQ(args.size(), 2);

  ASSERT_TRUE(!(args[0] < first || first < args[0]));
  ASSERT_TRUE(!(args[1] < second || second < args[1]));
}

TEST(AppBuilder, arg_invariant_not_nullptr) {
  std::shared_ptr<chimp::Arg> null;
  std::shared_ptr<chimp::Arg> not_null =
    chimp::ArgBuilder("not_null").takes_value(true).build();

  auto builder = chimp::AppBuilder("test");

  ASSERT_NO_THROW(builder.arg(not_null));
  ASSERT_THROW(builder.arg(null), chimp::LogicError);
}

TEST(AppBuilder, arg_invariant_unique_flags) {
  std::shared_ptr<chimp::Arg> a, b, c;

  a = chimp::ArgBuilder("a").short_arg('a').long_arg("aaa").build();
  b = chimp::ArgBuilder("b").short_arg('b').long_arg("bbb").build();
  c = chimp::ArgBuilder("c").short_arg('c').long_arg("ccc").build();

  auto builder = chimp::AppBuilder("test");

  ASSERT_NO_THROW(builder.arg(a));
  ASSERT_NO_THROW(builder.arg(b));
  ASSERT_NO_THROW(builder.arg(c));

  ASSERT_THROW(builder.arg(b), chimp::LogicError);

  ASSERT_THROW(builder.arg(chimp::ArgBuilder("test").short_arg('a').build()),
               chimp::LogicError);
  ASSERT_THROW(builder.arg(chimp::ArgBuilder("test").long_arg("aaa").build()),
               chimp::LogicError);
  ASSERT_THROW(
    builder.arg(
      chimp::ArgBuilder("test").short_arg('c').long_arg("ccc").build()),
    chimp::LogicError);

  ASSERT_NO_THROW(builder.arg(
    chimp::ArgBuilder("test").short_arg('d').long_arg("ddd").build()));
}
