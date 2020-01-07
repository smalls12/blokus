#pragma once

#include "INetworkConfigure.hpp"
#include "INetworkSend.hpp"
#include "Message.hpp"

class RegisterResponse
{
    public:
        RegisterResponse(INetworkConfigure& config, INetworkSend& send, std::string username, std::string gameName, IRegisterMessage& message);
        ~RegisterResponse();

        bool SendRegistrationSuccessfulResponse(IRegistrationSuccessful& successful);
        bool SendRegistrationUnsuccessfulResponse(IRegistrationUnsuccessful& unsuccessful);

    private:
        INetworkConfigure&  mConfig;
        INetworkSend&       mSend;
        std::string         mUsername;
        std::string         mGameName;
        IRegisterMessage&   mMessage;
};