#pragma once

#include "INetworkSend.hpp"
#include "IRequest.hpp"

#include "spdlog/spdlog.h"

class StartGame
{
    public:
        StartGame(INetworkSend& send, IRequest& request);
        ~StartGame();

        bool Start(std::string gameName);

    private:
        INetworkSend&   mSend;
        IRequest&       mRequest;
};