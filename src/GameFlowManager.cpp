#include "GameFlowManager.hpp"

#include "spdlog/spdlog.h"

GameFlowManager::GameFlowManager(IGameSettings& settings)
:   mSettings(settings),
    mCurrentPlayersTurn(0),
    mPlayers()
{
    spdlog::get("console")->info("GameFlowManager::GameFlowManager()");

    switch(mSettings.GetGameConfiguration())
    {
        case GameConfiguration::TWO_PLAYER:
        {
            mPlayers.push_back(PlayerId::PLAYER_ONE);
            mPlayers.push_back(PlayerId::PLAYER_TWO);
            break;
        }
        case GameConfiguration::FOUR_PLAYER:
        {
            mPlayers.push_back(PlayerId::PLAYER_ONE);
            mPlayers.push_back(PlayerId::PLAYER_TWO);
            mPlayers.push_back(PlayerId::PLAYER_THREE);
            mPlayers.push_back(PlayerId::PLAYER_FOUR);
            break;
        }
        default:
        {
            spdlog::get("console")->info("GameFlowManager::GameFlowManager() - Unhandled Game Configuration.");
            break;
        }
    }
}

GameFlowManager::~GameFlowManager()
{
    spdlog::get("console")->info("GameFlowManager::~GameFlowManager()");
}

PlayerId GameFlowManager::NextPlayersTurn()
{
    spdlog::get("console")->info("GameFlowManager::NextPlayersTurn()");

    mCurrentPlayersTurn++;
    switch(mSettings.GetGameConfiguration())
    {
        case GameConfiguration::TWO_PLAYER:
        {
            if( mCurrentPlayersTurn >= 2  )
            {
                mCurrentPlayersTurn = 0;
            }

            break;
        }
        case GameConfiguration::FOUR_PLAYER:
        {
            if( mCurrentPlayersTurn >= 4  )
            {
                mCurrentPlayersTurn = 0;
            }

            break;
        }
        default:
        {
            spdlog::get("console")->info("GameFlowManager::NextPlayersTurn() - Unhandled Game Configuration.");
            break;
        }
    }

    return mPlayers.at(mCurrentPlayersTurn);
}