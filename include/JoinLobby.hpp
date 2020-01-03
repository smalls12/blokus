#pragma once

#include "NetworkConnection.hpp"

class JoinLobby
{
    public:
        JoinLobby(NetworkConnection& connection, std::string lobbyName = std::string("BLOKUS"));
        ~JoinLobby();

    private:
        NetworkConnection&  mConnection;
        std::string         mLobbyName;
};