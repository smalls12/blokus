#include "PlayerScores.hpp"

#include "spdlog/spdlog.h"

PlayerScores::PlayerScores(IGameSettings& settings)
:   mSettings(settings),
    mPlayers()
{
    spdlog::get("console")->info("PlayerScores::PlayerScores()");

    switch(mSettings.GetGameConfiguration())
    {
        case GameConfiguration::TWO_PLAYER:
        {
            mPlayers.insert(std::pair<PlayerId, unsigned int>(PlayerId::PLAYER_ONE, 0));
            mPlayers.insert(std::pair<PlayerId, unsigned int>(PlayerId::PLAYER_TWO, 0));
            break;
        }
        case GameConfiguration::FOUR_PLAYER:
        {
            mPlayers.insert(std::pair<PlayerId, unsigned int>(PlayerId::PLAYER_ONE, 0));
            mPlayers.insert(std::pair<PlayerId, unsigned int>(PlayerId::PLAYER_TWO, 0));
            mPlayers.insert(std::pair<PlayerId, unsigned int>(PlayerId::PLAYER_THREE, 0));
            mPlayers.insert(std::pair<PlayerId, unsigned int>(PlayerId::PLAYER_FOUR, 0));
            break;
        }
        default:
        {
            spdlog::get("console")->info("PlayerScores::PlayerScores() - Unhandled Game Configuration.");
            break;
        }
    }
}

PlayerScores::~PlayerScores()
{
    spdlog::get("console")->info("PlayerScores::~PlayerScores()");
}

unsigned int PlayerScores::GetScore(PlayerId id)
{
    return mPlayers.at(id);
}

void PlayerScores::AddToScore(PlayerId id, unsigned int score)
{
    spdlog::get("console")->info("PlayerScores::AddToScore()");

    unsigned int temp = mPlayers.at(id);
    mPlayers.at(id) = temp + score;
}