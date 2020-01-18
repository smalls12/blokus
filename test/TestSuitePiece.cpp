#include <iostream>

#include "gtest/gtest.h"

#include "Piece.hpp"

class TestSuitePiece : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuitePiece() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuitePiece() {
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
TEST_F(TestSuitePiece, LayoutConstructor)
{
	Layout layout;
    Piece piece(layout);
}

TEST_F(TestSuitePiece, TestLayout)
{
	Layout layout;
    Piece piece(layout);

	EXPECT_TRUE(layout == piece.GetLayout());
}

TEST_F(TestSuitePiece, TestPadding)
{
	Layout layout;
    Piece piece(layout);

	Padding padding(5, 5, 5, 5);
	EXPECT_TRUE(padding == piece.GetPadding());
}
// }  // namespace - could surround Project1Test in a namespace