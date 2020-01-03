#include "JoinLobby.hpp"

#include "spdlog/spdlog.h"

JoinLobby::JoinLobby(NetworkConnection& connection, std::string lobbyName)
:   mConnection(connection),
    mLobbyName(lobbyName)
{
    spdlog::get("console")->info("JoinLobby::JoinLobby()");

    int rc = 0;
    rc = zyre_join(mConnection.Get(), mLobbyName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("JoinLobby::JoinLobby() - Could not start node.");
    }
}

JoinLobby::~JoinLobby()
{
    spdlog::get("console")->info("JoinLobby::~JoinLobby()");

    int rc = 0;
    rc = zyre_leave(mConnection.Get(), mLobbyName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("JoinLobby::~JoinLobby() - Could not start node.");
    }
}