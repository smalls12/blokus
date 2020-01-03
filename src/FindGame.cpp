#include "FindGame.hpp"

FindGame::FindGame(NetworkConnection& connection, ActiveGameManager& activeGameManager)
:   mConnection(connection),
    mActiveGameManager(activeGameManager)
{
    spdlog::get("console")->info("FindGame::FindGame");

    int rc = 0;
    rc = zyre_start(mConnection.Get());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("FindGame::FindGame - Could not start node.");
    }
}

FindGame::~FindGame()
{
    spdlog::get("console")->info("FindGame::~FindGame");
    
    zyre_stop(mConnection.Get());
}