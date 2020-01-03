#pragma once

#include "NetworkConnection.hpp"

class StartGame
{
    public:
        StartGame(NetworkConnection& connection, std::string gameName = std::string("BLOKUS"));
        ~StartGame();
        
        std::string GetUuid();

    private:
        NetworkConnection&  mConnection;
        std::string         mGameName;
};