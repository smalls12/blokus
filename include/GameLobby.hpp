#pragma once

/* =========================================================
 *
 * GameLobby.hpp
 * 
 * Concrete implementation for the game lobby
 * 
 * The game lobby settings are stored in the settings passed into the constructor
 * The game lobby will use INetworkSend to actually send messages to the lobby
 * 
 * ========================================================= */

#include "IGameLobby.hpp"
#include "IGameSettings.hpp"
#include "INetworkSend.hpp"

#include "spdlog/spdlog.h"

class GameLobby : public IGameLobby
{
    public:
        GameLobby(IGameSettings& settings, INetworkSend& send);
        ~GameLobby();

        bool SendMessageToLobby(std::string data);

    private:
        IGameSettings&          mSettings;
        INetworkSend&           mSend;
};