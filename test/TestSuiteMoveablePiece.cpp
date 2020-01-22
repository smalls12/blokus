#include <iostream>

#include "gtest/gtest.h"

#include "MoveablePiece.hpp"

class TestSuiteMoveablePiece : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteMoveablePiece() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuiteMoveablePiece() {
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
TEST_F(TestSuiteMoveablePiece, PieceConstructor)
{
	Layout layout;
	Piece piece(layout);
    MoveablePiece moveablePiece(piece);
}

TEST_F(TestSuiteMoveablePiece, TestLayout)
{
	Layout layout;
	Piece piece(layout);
    MoveablePiece moveablePiece(piece);

	EXPECT_TRUE(layout == moveablePiece.GetLayout());
}

TEST_F(TestSuiteMoveablePiece, TestLayoutExplicitObject)
{
	Layout layout;
	layout.Set( Point(2, 2), GridSquare::PLAYER_ONE );
	Piece piece(layout);
    MoveablePiece moveablePiece(piece);

	Layout layout_test;
	layout_test.Set( Point(2, 2), GridSquare::PLAYER_ONE );
	EXPECT_TRUE(layout_test == moveablePiece.GetLayout());
}

TEST_F(TestSuiteMoveablePiece, TestPadding)
{
	Layout layout;
	Piece piece(layout);
    MoveablePiece moveablePiece(piece);

	Padding padding(5, 5, 5, 5);
	EXPECT_TRUE(padding == moveablePiece.GetPadding());
}

TEST_F(TestSuiteMoveablePiece, CopyPieceIntoMoveablePiece)
{
	Layout layout;
	layout.Set( Point(2, 2), GridSquare::PLAYER_ONE );
	Piece piece(layout);
    MoveablePiece moveablePiece(piece);

	Padding padding(2, 2, 2, 2);
	EXPECT_TRUE(layout == moveablePiece.GetLayout());
	EXPECT_TRUE(padding == moveablePiece.GetPadding());
}

TEST_F(TestSuiteMoveablePiece, SetPlayed)
{
	Layout layout;
	layout.Set( Point(2, 2), GridSquare::PLAYER_ONE );
	Piece piece(layout);
    MoveablePiece moveablePiece(piece);

	EXPECT_FALSE(moveablePiece.HasPieceBeenPlayed());
	moveablePiece.PiecePlayed();
	EXPECT_TRUE(moveablePiece.HasPieceBeenPlayed());
}

// }  // namespace - could surround Project1Test in a namespace