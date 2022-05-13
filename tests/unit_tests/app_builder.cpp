#include <gtest/gtest.h>

#include "chimp/chimp.h"

class chimp::testing::AppBuilderTest {};

using chimp::testing::AppBuilderTest;

TEST(AppBuilder, basic_assertion) { ASSERT_EQ(2 + 2, 4); }
