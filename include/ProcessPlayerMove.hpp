#pragma once

#include "IGameLobby.hpp"
#include "IPlayerMoveRequest.hpp"

#include "spdlog/spdlog.h"

class ProcessPlayerMove
{
    public:
        ProcessPlayerMove(IGameLobby& lobby, IPlayerMoveRequest& request);
        ~ProcessPlayerMove();

        bool Process(IPlayerMoveRequestData& data);

    private:
        IGameLobby&             mLobby;
        IPlayerMoveRequest&     mRequest;
};