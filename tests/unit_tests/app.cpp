#include <gtest/gtest.h>

#include "chimp_testing_classes.h"

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
