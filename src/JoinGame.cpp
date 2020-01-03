#include "JoinGame.hpp"

#include "spdlog/spdlog.h"

JoinGame::JoinGame(NetworkConnection& connection, std::string gameName)
:   mConnection(connection),
    mGameName(gameName)
{
    spdlog::get("console")->info("JoinGame::JoinGame()");

    int rc = 0;
    rc = zyre_start(mConnection.Get());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("JoinGame::JoinGame() - Could not start node.");
    }

    rc = zyre_join(mConnection.Get(), mGameName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("JoinGame::JoinGame() - Could not join game.");
    }

    zclock_sleep(250);
}

JoinGame::~JoinGame()
{
    spdlog::get("console")->info("JoinGame::~JoinGame()");

    int rc = 0;
    rc = zyre_leave(mConnection.Get(), mGameName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("JoinGame::~JoinGame() - Error leaving game.");
    }

    zyre_stop(mConnection.Get());
}

std::string JoinGame::GetUuid()
{
    return std::string( zyre_uuid( mConnection.Get() ) );
}