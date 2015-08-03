#include "gtest/gtest.h"

double sum(double a, double b);

TEST(SquareRootTest, PositiveNos) {
	EXPECT_EQ(11.0, sum(5, 6));
	EXPECT_EQ(25, sum(16, 9));
	EXPECT_EQ(2037, sum(1013, 1024));
}

TEST(SquareRootTest, ZeroAndNegativeNos) {
	ASSERT_EQ(0.0, sum(0, 0));
	ASSERT_EQ(-1, sum(-22, 0));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	int result = RUN_ALL_TESTS();
	system("pause");
	return result;
}

double sum(double a, double b)
{
	return a + b;
}