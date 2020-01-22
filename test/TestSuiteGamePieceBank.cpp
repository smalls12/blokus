#include <iostream>

#include "gtest/gtest.h"

#include "GamePieceBank.hpp"

class TestSuiteGamePieceBank : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteGamePieceBank() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuiteGamePieceBank() {
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
TEST_F(TestSuiteGamePieceBank, Constructor)
{
	GamePieceBank gamePieceBank;
}

TEST_F(TestSuiteGamePieceBank, ReferenceReturn)
{
	GamePieceBank gamePieceBank;

    MoveablePiece* moveablePieceBefore = gamePieceBank.GetPlayerPiece(PlayerId::PLAYER_ONE, PieceType::I1);
    EXPECT_FALSE(moveablePieceBefore->HasPieceBeenPlayed());
    moveablePieceBefore->PiecePlayed();

    MoveablePiece* moveablePieceAfter = gamePieceBank.GetPlayerPiece(PlayerId::PLAYER_ONE, PieceType::I1);
    EXPECT_TRUE(moveablePieceAfter->HasPieceBeenPlayed());
}
// }  // namespace - could surround Project1Test in a namespace