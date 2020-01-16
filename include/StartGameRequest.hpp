#pragma once

/* =========================================================
 *
 * StartGameRequest.hpp
 * 
 * Concrete implementation for building the start game request
 * 
 * The start game message requries the UUID from INetworkConfig
 * The start game message will be built using the IStartGameMessage
 * 
 * ========================================================= */

#include "IRequest.hpp"
#include "IStartGameMessage.hpp"
#include "IMessageBase.hpp"

#include "spdlog/spdlog.h"

class StartGameRequest : public IRequest
{
    public:
        StartGameRequest(IStartGameMessage& message, IMessageBase& base);
        ~StartGameRequest();

        std::string Build();

    private:
        IStartGameMessage&      mMessage;
        IMessageBase&           mBase;
};