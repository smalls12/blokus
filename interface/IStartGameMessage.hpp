#pragma once

/* =========================================================
 *
 * IStartGameMessage.hpp
 * 
 * Encapsulates building and parsing the message that indicates
 * the start of the game 
 * 
 * These messages are blank and require no meta data
 * 
 * ========================================================= */

#include "IMessageBase.hpp"
#include "IStartGameRequestData.hpp"

#include <string>

class IStartGameMessage
{
    public:
        virtual std::string BuildStartGameRequestMessage(IMessageBase& base, IStartGameRequestData& data) = 0;

        virtual bool ParseStartGameRequestMessage(std::string message, IStartGameRequestData& data) = 0;

};