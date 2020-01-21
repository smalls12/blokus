#include <iostream>

#include "gtest/gtest.h"

#include "GameFlowManager.hpp"

#include "Game.hpp"

class TestSuiteGameFlowManager : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteGameFlowManager() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuiteGameFlowManager() {
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
TEST_F(TestSuiteGameFlowManager, Constructor)
{
    Game game;
	GameFlowManager gameFlowManager(game);
}

TEST_F(TestSuiteGameFlowManager, TwoPlayer)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
	GameFlowManager gameFlowManager(game);
}

TEST_F(TestSuiteGameFlowManager, FourPlayer)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	GameFlowManager gameFlowManager(game);
}

TEST_F(TestSuiteGameFlowManager, TwoPlayer_GetNextPlayerOnce)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
	GameFlowManager gameFlowManager(game);

    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_TWO );
}

TEST_F(TestSuiteGameFlowManager, TwoPlayer_GetNextPlayerTwice_Rollover)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
	GameFlowManager gameFlowManager(game);

    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_TWO );
    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_ONE );
}

TEST_F(TestSuiteGameFlowManager, FourPlayer_GetNextPlayerOnce)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	GameFlowManager gameFlowManager(game);

    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_TWO );
}

TEST_F(TestSuiteGameFlowManager, FourPlayer_GetNextPlayerTwice)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	GameFlowManager gameFlowManager(game);

    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_TWO );
    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_THREE );
}

TEST_F(TestSuiteGameFlowManager, FourPlayer_GetNextPlayerFourTimes_Rollover)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	GameFlowManager gameFlowManager(game);

    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_TWO );
    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_THREE );
    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_FOUR );
    EXPECT_TRUE( gameFlowManager.NextPlayersTurn() == PlayerId::PLAYER_ONE );
}
// }  // namespace - could surround Project1Test in a namespace