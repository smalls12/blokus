#pragma once

#include "IGameLobby.hpp"
#include "IChatRequest.hpp"
#include "IChatRequestData.hpp"

class ProcessChatMessage
{
    public:
        ProcessChatMessage(IGameLobby& lobby, IChatRequest& request);
        ~ProcessChatMessage();

        bool Process(IChatRequestData& data);

    private:
        IGameLobby&             mLobby;
        IChatRequest&           mRequest;
};