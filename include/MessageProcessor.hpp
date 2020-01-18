#pragma once

#include "IRegisterMessage.hpp"

#include "IRegisterRequest.hpp"
#include "IRegistrationSuccessful.hpp"
#include "IRegistrationUnsuccessful.hpp"

#include "IPlayerMoveRequestData.hpp"

#include "spdlog/spdlog.h"

class MessageProcessor
{
    public:
        MessageProcessor();
        ~MessageProcessor();

        bool ProcessMessage(std::string data);

        // Registration
        void SetRegisterRequestEndpoint(std::function<bool(IRegisterRequest&)> func) { mRegistrationRequestEndpoint = func; }
        void SetRegistrationSuccessfulEndpoint(std::function<bool(IRegistrationSuccessful&)> func) { mRegistrationSuccessfulEndpoint = func; }
        void SetRegistrationUnsuccessfulEndpoint(std::function<bool(IRegistrationUnsuccessful&)> func) { mRegistrationUnsuccessfulEndpoint = func; }

        // Start Game
        void SetStartGameEndpoint(std::function<bool()> func) { mStartGameEndpoint = func; }

        // Player Move
        void SetPlayerMoveEndpoint(std::function<bool(IPlayerMoveRequestData&)> func) { mPlayerMoveEndpoint = func; }

    private:
        // Registration
        std::function<bool(IRegisterRequest&)>                  mRegistrationRequestEndpoint;
        std::function<bool(IRegistrationSuccessful&)>           mRegistrationSuccessfulEndpoint;
        std::function<bool(IRegistrationUnsuccessful&)>         mRegistrationUnsuccessfulEndpoint;

        // Start Game
        std::function<bool()>                                   mStartGameEndpoint;

        // Player Move
        std::function<bool(IPlayerMoveRequestData&)>            mPlayerMoveEndpoint;
};