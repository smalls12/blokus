#include "PlayerTurnManager.hpp"

#include "spdlog/spdlog.h"

PlayerTurnManager::PlayerTurnManager(IGameSettings& settings)
:   mSettings(settings),
    mCurrentPlayersTurn(0),
    mPlayers()
{
    spdlog::get("console")->info("PlayerTurnManager::PlayerTurnManager()");

    switch(mSettings.GetGameConfiguration())
    {
        case GameConfiguration::TWO_PLAYER:
        {
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_ONE, PlayerColor::BLUE));
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_TWO, PlayerColor::RED));
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_ONE, PlayerColor::YELLOW));
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_TWO, PlayerColor::GREEN));
            break;
        }
        case GameConfiguration::FOUR_PLAYER:
        {
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_ONE, PlayerColor::BLUE));
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_TWO, PlayerColor::RED));
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_THREE, PlayerColor::YELLOW));
            mPlayers.push_back(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_FOUR, PlayerColor::GREEN));
            break;
        }
        default:
        {
            spdlog::get("console")->info("PlayerTurnManager::PlayerTurnManager() - Unhandled Game Configuration.");
            break;
        }
    }
}

PlayerTurnManager::~PlayerTurnManager()
{
    spdlog::get("console")->info("PlayerTurnManager::~PlayerTurnManager()");
}

std::pair<PlayerId, PlayerColor> PlayerTurnManager::NextPlayersTurn()
{
    spdlog::get("console")->info("PlayerTurnManager::NextPlayersTurn()");

    mCurrentPlayersTurn++;
    if( mCurrentPlayersTurn >= 4  )
    {
        mCurrentPlayersTurn = 0;
    }

    return mPlayers.at(mCurrentPlayersTurn);
}