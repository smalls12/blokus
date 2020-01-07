#pragma once

#include "INetworkSend.hpp"
#include "IRegisterRequest.hpp"
#include "IRegisterMessage.hpp"

#include "spdlog/spdlog.h"

class RegisterForGame
{
    public:
        RegisterForGame(INetworkSend& send, IRegisterRequest& request, IRegisterMessage& message);
        ~RegisterForGame();

        bool Register(std::string gameName);

    private:
        INetworkSend&       mSend;
        IRegisterRequest&   mRegisterRequest;
        IRegisterMessage&   mRegisterMessage;
};