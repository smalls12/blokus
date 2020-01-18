#include <iostream>

#include "gtest/gtest.h"

#include "Padding.hpp"

class TestSuitePadding : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuitePadding() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuitePadding() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Project1.
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(TestSuitePadding, Constructor)
{
	Padding padding;
}

TEST_F(TestSuitePadding, PaddingDefault)
{
	Padding padding;

    EXPECT_EQ(padding.GetLeft(), 0);
    EXPECT_EQ(padding.GetTop(), 0);
    EXPECT_EQ(padding.GetRight(), 0);
    EXPECT_EQ(padding.GetBottom(), 0);
}

TEST_F(TestSuitePadding, PaddingCompareEqual1)
{
	Padding padding1(0, 1, 0, 0);
	Padding padding2(0, 1, 0, 0);

	EXPECT_TRUE(padding1 == padding2);
}

TEST_F(TestSuitePadding, PaddingCompareEqual2)
{
	Padding padding1(0, 1, 1, 0);
	Padding padding2(0, 1, 1, 0);

	EXPECT_TRUE(padding1 == padding2);
}

TEST_F(TestSuitePadding, PaddingCompareNotEqual1)
{
	Padding padding1(0, 1, 0, 0);
	Padding padding2(0, 1, 1, 0);

	EXPECT_FALSE(padding1 == padding2);
}

TEST_F(TestSuitePadding, PaddingCompareNotEqual2)
{
	Padding padding1(0, 1, 0, 0);
	Padding padding2(0, 0, 0, 0);

	EXPECT_FALSE(padding1 == padding2);
}
// }  // namespace - could surround Project1Test in a namespace