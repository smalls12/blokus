#include <iostream>

#include "gtest/gtest.h"

#include "PieceSelector.hpp"

class TestSuitePieceSelector : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuitePieceSelector() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuitePieceSelector() {
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
TEST_F(TestSuitePieceSelector, Initialize)
{
    PieceSelector pieceSelector;
}

TEST_F(TestSuitePieceSelector, FirstElement)
{
    PieceSelector pieceSelector;
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I1 );
}

TEST_F(TestSuitePieceSelector, SecondElement)
{
    PieceSelector pieceSelector;
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I1 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I2 );
}

TEST_F(TestSuitePieceSelector, FullWrapAround)
{
    PieceSelector pieceSelector;
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I1 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I2 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::V3 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I3 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::O );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::T4 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I4 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::L4 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::Z4 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::L5 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::T5 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::V5 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::N );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::Z5 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I5 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::P );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::W );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::U );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::F );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::X );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I1 );
    EXPECT_EQ( pieceSelector.GetNextPiece(), PieceType::I2 );
}

// }  // namespace - could surround Project1Test in a namespace