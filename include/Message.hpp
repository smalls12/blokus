#pragma once

// this file helps build messages for transport

// protobuf header
#include <protobuf/blokus.pb.h>

#include "IRegisterMessage.hpp"
#include "MessageType.hpp"
#include "IRegisterRequest.hpp"

#include <Player.hpp>
#include <PieceMove.hpp>

class Message : public IRegisterMessage
{
    public:
        Message();
        ~Message();

        // ==============================================================================================================
        // Registration
        // ==============================================================================================================
        std::string BuildRegistrationRequestMessage(IRegisterRequest& message);
        std::string BuildRegistrationResponseMessage(IRegistrationSuccessful& message);
        std::string BuildRegistrationResponseMessage(IRegistrationUnsuccessful& message);

        bool ParseRegistrationRequestMessage(std::string message, IRegisterRequest& request);
        bool ParseRegistrationResponseMessage(std::string message, IRegistrationSuccessful& sucessful, IRegistrationUnsuccessful& unsuccesful);
        // ==============================================================================================================

    private:
        
};
