#include "FindGame.hpp"

FindGame::FindGame(INetworkSearch& search, ActiveGameManager& activeGameManager)
:   mSearch(search),
    mActiveGameManager(activeGameManager)
{
    spdlog::get("console")->info("FindGame::FindGame");
}

FindGame::~FindGame()
{
    spdlog::get("console")->info("FindGame::~FindGame");
}