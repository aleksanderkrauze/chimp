#include <gtest/gtest.h>

#include "chimp/chimp.h"

class chimp::testing::AppTest {};

using chimp::testing::AppTest;

TEST(App, basic_assertion) { ASSERT_EQ(2 + 2, 4); }
