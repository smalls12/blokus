#pragma once

/* =========================================================
 *
 * IPlayerMoveMessage.hpp
 * 
 * Encapsulates building and parsing the message that indicates
 * the move performed by a player 
 * 
 * ========================================================= */

#include "IMessageBase.hpp"
#include "IPlayerMoveRequestData.hpp"

#include <string>

class IPlayerMoveMessage
{
    public:
        virtual std::string BuildPlayerMoveRequestMessage(IMessageBase& base, IPlayerMoveRequestData& request) = 0;

        virtual bool ParsePlayerMoveRequestMessage(std::string message, IPlayerMoveRequestData& data) = 0;

};