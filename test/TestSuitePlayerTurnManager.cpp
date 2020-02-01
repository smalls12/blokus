#include <iostream>

#include "gtest/gtest.h"

#include "PlayerTurnManager.hpp"

#include "Game.hpp"

class TestSuitePlayerTurnManager : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuitePlayerTurnManager() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuitePlayerTurnManager() {
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
TEST_F(TestSuitePlayerTurnManager, Constructor)
{
    Game game;
	PlayerTurnManager playerTurnManager(game);
}

TEST_F(TestSuitePlayerTurnManager, TwoPlayer)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
	PlayerTurnManager playerTurnManager(game);
}

TEST_F(TestSuitePlayerTurnManager, FourPlayer)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	PlayerTurnManager playerTurnManager(game);
}

TEST_F(TestSuitePlayerTurnManager, TwoPlayer_GetNextPlayerOnce)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
	PlayerTurnManager playerTurnManager(game);

	std::pair<PlayerId, PlayerColor> nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_TWO );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::RED );
}

TEST_F(TestSuitePlayerTurnManager, TwoPlayer_GetNextPlayerTwice)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
	PlayerTurnManager playerTurnManager(game);

	std::pair<PlayerId, PlayerColor> nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_TWO );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::RED );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_ONE );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::YELLOW );
}

TEST_F(TestSuitePlayerTurnManager, TwoPlayer_GetNextPlayerFourTimes_Rollover)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
	PlayerTurnManager playerTurnManager(game);

	std::pair<PlayerId, PlayerColor> nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_TWO );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::RED );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_ONE );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::YELLOW );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_TWO );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::GREEN );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_ONE );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::BLUE );
}

TEST_F(TestSuitePlayerTurnManager, FourPlayer_GetNextPlayerOnce)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	PlayerTurnManager playerTurnManager(game);

	std::pair<PlayerId, PlayerColor> nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_TWO );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::RED );
}

TEST_F(TestSuitePlayerTurnManager, FourPlayer_GetNextPlayerTwice)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	PlayerTurnManager playerTurnManager(game);

	std::pair<PlayerId, PlayerColor> nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_TWO );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::RED );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_THREE );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::YELLOW );
}

TEST_F(TestSuitePlayerTurnManager, FourPlayer_GetNextPlayerFourTimes_Rollover)
{
    Game game;
    game.SetGameConfiguration(GameConfiguration::FOUR_PLAYER);
	PlayerTurnManager playerTurnManager(game);

	std::pair<PlayerId, PlayerColor> nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_TWO );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::RED );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_THREE );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::YELLOW );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_FOUR );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::GREEN );

	nextPlayer = playerTurnManager.NextPlayersTurn();
    EXPECT_TRUE( nextPlayer.first == PlayerId::PLAYER_ONE );
	EXPECT_TRUE( nextPlayer.second == PlayerColor::BLUE );
}

// }  // namespace - could surround Project1Test in a namespace