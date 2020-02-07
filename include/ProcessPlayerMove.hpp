#pragma once

#include "IGameLobby.hpp"
#include "IPlayerMoveRequest.hpp"

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