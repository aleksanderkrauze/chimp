#include <gtest/gtest.h>

#include "chimp/chimp.h"

using chimp::Error;
using chimp::LogicError;
using chimp::ParsingError;

TEST(Error, throw) {
  try {
    throw Error{"message"};
  } catch (const Error& e) {
    ASSERT_STREQ(e.what(), "message");
  }
}

TEST(Error, catch_as_std_exception) {
  try {
    throw Error{"message"};
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "message");
  }
}

TEST(LogicError, throw) {
  try {
    throw LogicError{"logic error"};
  } catch (const LogicError& e) {
    ASSERT_STREQ(e.what(), "logic error");
  }
}

TEST(LogicError, catch_as_Error) {
  try {
    throw LogicError{"logic error"};
  } catch (const Error& e) {
    ASSERT_STREQ(e.what(), "logic error");
  }
}

TEST(ParsingError, throw) {
  try {
    throw ParsingError{"logic error"};
  } catch (const ParsingError& e) {
    ASSERT_STREQ(e.what(), "logic error");
  }
}

TEST(ParsingError, catch_as_Error) {
  try {
    throw ParsingError{"logic error"};
  } catch (const Error& e) {
    ASSERT_STREQ(e.what(), "logic error");
  }
}