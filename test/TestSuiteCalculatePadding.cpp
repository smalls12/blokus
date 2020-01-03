#include <iostream>

#include "gtest/gtest.h"

#include "Layout.hpp"
#include "CalculatePadding.hpp"

class TestSuiteCalculatePadding : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteCalculatePadding() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuiteCalculatePadding() {
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
TEST_F(TestSuiteCalculatePadding, BlankLayout)
{
    Layout tmp_layout;
    Padding tmp_padding = CalculatePadding::CalculatePaddingFromLayout(tmp_layout);

	EXPECT_EQ(tmp_padding.GetLeft(), 5);
    EXPECT_EQ(tmp_padding.GetTop(), 5);
    EXPECT_EQ(tmp_padding.GetRight(), 5);
    EXPECT_EQ(tmp_padding.GetBottom(), 5);
}

TEST_F(TestSuiteCalculatePadding, EvenPadding)
{
    Layout tmp_layout;
    tmp_layout.Set( Point(2, 2), GridSquare::P1 );
    Padding tmp_padding = CalculatePadding::CalculatePaddingFromLayout(tmp_layout);

	EXPECT_EQ(tmp_padding.GetLeft(), 2);
    EXPECT_EQ(tmp_padding.GetTop(), 2);
    EXPECT_EQ(tmp_padding.GetRight(), 2);
    EXPECT_EQ(tmp_padding.GetBottom(), 2);
}

TEST_F(TestSuiteCalculatePadding, ShallowTopPadding)
{
    Layout tmp_layout;
    tmp_layout.Set( Point(1, 2), GridSquare::P1 );
    tmp_layout.Set( Point(2, 2), GridSquare::P1 );
    Padding tmp_padding = CalculatePadding::CalculatePaddingFromLayout(tmp_layout);

	EXPECT_EQ(tmp_padding.GetLeft(), 2);
    EXPECT_EQ(tmp_padding.GetTop(), 1);
    EXPECT_EQ(tmp_padding.GetRight(), 2);
    EXPECT_EQ(tmp_padding.GetBottom(), 2);
}

TEST_F(TestSuiteCalculatePadding, ShallowBottomPadding)
{
    Layout tmp_layout;
    tmp_layout.Set( Point(2, 2), GridSquare::P1 );
    tmp_layout.Set( Point(3, 2), GridSquare::P1 );
    Padding tmp_padding = CalculatePadding::CalculatePaddingFromLayout(tmp_layout);

	EXPECT_EQ(tmp_padding.GetLeft(), 2);
    EXPECT_EQ(tmp_padding.GetTop(), 2);
    EXPECT_EQ(tmp_padding.GetRight(), 2);
    EXPECT_EQ(tmp_padding.GetBottom(), 1);
}

TEST_F(TestSuiteCalculatePadding, ShallowLeftPadding)
{
    Layout tmp_layout;
    tmp_layout.Set( Point(2, 1), GridSquare::P1 );
    tmp_layout.Set( Point(2, 2), GridSquare::P1 );
    Padding tmp_padding = CalculatePadding::CalculatePaddingFromLayout(tmp_layout);

	EXPECT_EQ(tmp_padding.GetLeft(), 1);
    EXPECT_EQ(tmp_padding.GetTop(), 2);
    EXPECT_EQ(tmp_padding.GetRight(), 2);
    EXPECT_EQ(tmp_padding.GetBottom(), 2);
}

TEST_F(TestSuiteCalculatePadding, ShallowRightPadding)
{
    Layout tmp_layout;
    tmp_layout.Set( Point(2, 2), GridSquare::P1 );
    tmp_layout.Set( Point(2, 3), GridSquare::P1 );
    Padding tmp_padding = CalculatePadding::CalculatePaddingFromLayout(tmp_layout);

	EXPECT_EQ(tmp_padding.GetLeft(), 2);
    EXPECT_EQ(tmp_padding.GetTop(), 2);
    EXPECT_EQ(tmp_padding.GetRight(), 1);
    EXPECT_EQ(tmp_padding.GetBottom(), 2);
}

// }  // namespace - could surround Project1Test in a namespace