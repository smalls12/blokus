#include <iostream>

#include "gtest/gtest.h"

#include "Layout.hpp"

class TestSuiteLayout : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteLayout() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuiteLayout() {
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
TEST_F(TestSuiteLayout, Constructor)
{
	Layout layout;
}

TEST_F(TestSuiteLayout, ComparisonCheckDefault)
{
	Layout layout1;
    Layout layout2;

	EXPECT_TRUE(layout1 == layout2);
}

TEST_F(TestSuiteLayout, ComparisonCheckEqual1)
{
	Layout layout1;
    layout1.Set( Point(2, 2), GridSquare::P1 );
    Layout layout2;
    layout2.Set( Point(2, 2), GridSquare::P1 );

	EXPECT_TRUE(layout1 == layout2);
}

TEST_F(TestSuiteLayout, ComparisonCheckEqual2)
{
	Layout layout1;
    layout1.Set( Point(2, 2), GridSquare::P1 );
    layout1.Set( Point(2, 3), GridSquare::P1 );
    Layout layout2;
    layout2.Set( Point(2, 2), GridSquare::P1 );
    layout2.Set( Point(2, 3), GridSquare::P1 );

	EXPECT_TRUE(layout1 == layout2);
}

TEST_F(TestSuiteLayout, ComparisonCheckNotEqual1)
{
	Layout layout1;
    layout1.Set( Point(2, 2), GridSquare::P1 );
    Layout layout2;

	EXPECT_FALSE(layout1 == layout2);
}

TEST_F(TestSuiteLayout, ComparisonCheckNotEqual2)
{
	Layout layout1;
    layout1.Set( Point(1, 2), GridSquare::P1 );
    layout1.Set( Point(2, 3), GridSquare::P1 );
    Layout layout2;
    layout2.Set( Point(2, 2), GridSquare::P1 );
    layout2.Set( Point(2, 3), GridSquare::P1 );

	EXPECT_FALSE(layout1 == layout2);
}
// }  // namespace - could surround Project1Test in a namespace