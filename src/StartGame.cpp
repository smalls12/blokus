#include "StartGame.hpp"

#include "spdlog/spdlog.h"

StartGame::StartGame(NetworkConnection& connection, std::string gameName)
:   mConnection(connection),
    mGameName(gameName)
{
    spdlog::get("console")->info("StartGame::StartGame()");

    zyre_set_header(mConnection.Get(), "X-BLOKUS", "%s", mGameName.c_str());

    int rc = 0;
    rc = zyre_start(mConnection.Get());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("StartGame::StartGame() - Could not start node.");
    }

    rc = zyre_join(mConnection.Get(), mGameName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("StartGame::StartGame() - Could not start game.");
    }

    zclock_sleep(250);
}

StartGame::~StartGame()
{
    spdlog::get("console")->info("StartGame::~StartGame");

    int rc = 0;
    rc = zyre_leave(mConnection.Get(), mGameName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("StartGame::~StartGame() - Error leaving game.");
    }

    zyre_stop(mConnection.Get());
}

std::string StartGame::GetUuid()
{
    return std::string( zyre_uuid( mConnection.Get() ) );
}
