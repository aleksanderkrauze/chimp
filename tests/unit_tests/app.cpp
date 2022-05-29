#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

void call_parse(chimp::App& app, const std::vector<std::string>& args) {
  std::vector<const char*> c_args;

  for (const auto& arg : args) {
    c_args.push_back(arg.c_str());
  }

  app.parse(c_args.size(), c_args.data());
}

const auto tester = chimp::testing::AppTest();

TEST(App, member_variables_values_from_empty_builder) {
  const auto app = chimp::App::builder("test").build();

  ASSERT_STREQ(tester.m_name(app).c_str(), "test");

  // std::optionals are empty
  ASSERT_FALSE(tester.m_author(app));
  ASSERT_FALSE(tester.m_version(app));
  ASSERT_FALSE(tester.m_about(app));
}

TEST(App, member_variables_values_from_full_builder) {
  const auto app = chimp::App::builder("test")
                     .author("Some author")
                     .version("1.2.3")
                     .about("Short program description")
                     .build();

  ASSERT_STREQ(tester.m_author(app).value().c_str(), "Some author");
  ASSERT_STREQ(tester.m_version(app).value().c_str(), "1.2.3");
  ASSERT_STREQ(tester.m_about(app).value().c_str(),
               "Short program description");
}

TEST(App, parse_empty) {
  auto app = chimp::App::builder("app").build();

  std::vector<std::string> args{};

  ASSERT_NO_THROW(call_parse(app, args));
}

TEST(App, parse_named_arguments_were_present) {
  std::shared_ptr<chimp::Arg> a, b, c, d;

  auto app =
    chimp::App::builder("test")
      .arg(chimp::Arg::builder("a").short_arg('a').build(a))
      .arg(chimp::Arg::builder("b").long_arg("bbb").build(b))
      .arg(chimp::Arg::builder("c").short_arg('c').long_arg("ccc").build(c))
      .arg(chimp::Arg::builder("d").takes_value(true).build(d))
      .build();

  std::vector<std::string> args{"test", "-a", "--ccc"};
  ASSERT_NO_THROW(call_parse(app, args));

  ASSERT_TRUE(a->was_present());
  ASSERT_FALSE(b->was_present());
  ASSERT_TRUE(c->was_present());
}
