#pragma once

// this file helps build messages for transport

// protobuf header
#include <protobuf/blokus.pb.h>

#include "MessageType.hpp"

#include "IMessageBase.hpp"

#include "IRegisterMessage.hpp"
#include "IRegisterRequest.hpp"

#include "IStartGameMessage.hpp"

#include "IPlayerMoveMessage.hpp"
#include "IPlayerMoveRequestData.hpp"

#include <Player.hpp>
#include <PieceMove.hpp>

class Message : public IRegisterMessage, public IStartGameMessage, public IPlayerMoveMessage
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

        // ==============================================================================================================
        // Start
        // ==============================================================================================================
        std::string BuildStartGameRequestMessage(IMessageBase& base);

        bool ParseStartGameRequestMessage(std::string message);
        // ==============================================================================================================

        // ==============================================================================================================
        // Player Move
        // ==============================================================================================================
        std::string BuildPlayerMoveRequestMessage(IMessageBase& base, IPlayerMoveRequestData& data);

        bool ParsePlayerMoveRequestMessage(std::string message, IPlayerMoveRequestData& data);
        // ==============================================================================================================
        

    private:
        blokus::Piece ConvertPieceToMessageEnum(PieceType type);
        PieceType ParseMessageEnumToPiece(blokus::Piece type);

};
