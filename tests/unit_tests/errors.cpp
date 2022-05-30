#include <string>

#include <gtest/gtest.h>

#include "chimp/chimp.h"

using chimp::Error;
using chimp::LogicError;
using chimp::NotParsedYetError;
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
    throw LogicError{"message"};
  } catch (const LogicError& e) {
    ASSERT_STREQ(e.what(), "message");
  }
}

TEST(LogicError, catch_as_Error) {
  try {
    throw LogicError{"logic error"};
  } catch (const Error& e) {
    ASSERT_STREQ(e.what(), "logic error");
  }
}

TEST(NotParsedYetError, throw) {
  try {
    throw NotParsedYetError{"message"};
  } catch (const NotParsedYetError& e) {
    ASSERT_STREQ(e.what(), "message");
  }
}

TEST(NotParsedYetError, catch_as_LogicError) {
  try {
    throw NotParsedYetError{"message"};
  } catch (const LogicError& e) {
    ASSERT_STREQ(e.what(), "message");
  }
}

TEST(ParsingError, throw) {
  try {
    throw ParsingError{"message"};
  } catch (const ParsingError& e) {
    ASSERT_STREQ(e.what(), "message");
  }
}

TEST(ParsingError, catch_as_Error) {
  try {
    throw ParsingError{"message"};
  } catch (const Error& e) {
    ASSERT_STREQ(e.what(), "message");
  }
}

TEST(Common, variadic_constructors) {
  std::string one = "one ";

  try {
    throw Error{one, 2, " three"};
  } catch (const Error& e) {
    ASSERT_STREQ(e.what(), "one 2 three");
  }
  try {
    throw LogicError{one, 2, " three"};
  } catch (const LogicError& e) {
    ASSERT_STREQ(e.what(), "one 2 three");
  }
  try {
    throw NotParsedYetError{one, 2, " three"};
  } catch (const NotParsedYetError& e) {
    ASSERT_STREQ(e.what(), "one 2 three");
  }
  try {
    throw ParsingError{one, 2, " three"};
  } catch (const ParsingError& e) {
    ASSERT_STREQ(e.what(), "one 2 three");
  }
}
