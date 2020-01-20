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

#include "IStartGameMessage.hpp"
#include "IMessageBase.hpp"
#include "IStartGameRequest.hpp"

#include "spdlog/spdlog.h"

class StartGameRequest : public IStartGameRequest
{
    public:
        StartGameRequest(IStartGameMessage& message, IMessageBase& base);
        ~StartGameRequest();

        std::string Build(IStartGameRequestData& data);

    private:
        IStartGameMessage&      mMessage;
        IMessageBase&           mBase;
};