#pragma once

#include "INetworkReceive.hpp"
#include "GameNotification.hpp"

#include "spdlog/spdlog.h"

#include <string>

class ReadGameNotification
{
    public:
        ReadGameNotification(INetworkReceive& receive, std::string gameName);
        ~ReadGameNotification();

        bool CheckEvent();
        bool Receive(GameNotification &gm);

    private:
        INetworkReceive&    mReceive;
        std::string         mGameName;
};