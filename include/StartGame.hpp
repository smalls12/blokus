#pragma once

#include "INetworkSend.hpp"
#include "IStartGameRequest.hpp"

#include "IGameSettings.hpp"
#include "IPlayerRegistry.hpp"

#include "spdlog/spdlog.h"

class StartGame
{
    public:
        StartGame(INetworkSend& send, IStartGameRequest& request);
        ~StartGame();

        bool Start(IGameSettings& settings, IPlayerRegistry& registry);

    private:
        INetworkSend&               mSend;
        IStartGameRequest&          mRequest;
};