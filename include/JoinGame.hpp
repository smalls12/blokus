#pragma once

#include "NetworkConnection.hpp"

class JoinGame
{
    public:
        JoinGame(NetworkConnection& connection, std::string gameName = std::string("BLOKUS"));
        ~JoinGame();

        std::string GetUuid();

    private:
        NetworkConnection&  mConnection;
        std::string         mGameName;
};