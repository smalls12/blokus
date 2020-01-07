#pragma once

#include "IRegisterMessage.hpp"

#include "IRegisterRequest.hpp"
#include "IRegistrationSuccessful.hpp"
#include "IRegistrationUnsuccessful.hpp"

#include "spdlog/spdlog.h"

class MessageProcessor
{
    public:
        MessageProcessor(IRegisterMessage& message);
        ~MessageProcessor();

        bool ProcessMessage(std::string data);

        void SetRegisterRequestEndpoint(std::function<bool(IRegisterRequest&)> func) { mRegistrationRequestEndpoint = func; }
        void SetRegistrationSuccessfulEndpoint(std::function<bool(IRegistrationSuccessful&)> func) { mRegistrationSuccessfulEndpoint = func; }
        void SetRegistrationUnsuccessfulEndpoint(std::function<bool(IRegistrationUnsuccessful&)> func) { mRegistrationUnsuccessfulEndpoint = func; }

    private:
        std::function<bool(IRegisterRequest&)>               mRegistrationRequestEndpoint;
        std::function<bool(IRegistrationSuccessful&)>        mRegistrationSuccessfulEndpoint;
        std::function<bool(IRegistrationUnsuccessful&)>      mRegistrationUnsuccessfulEndpoint;

        IRegisterMessage&       mMessage;

};