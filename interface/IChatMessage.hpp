#pragma once

/* =========================================================
 *
 * IChatMessage.hpp
 * 
 * Encapsulates building and parsing the message that indicates
 * a chat message
 * 
 * ========================================================= */

#include "IMessageBase.hpp"
#include "IChatRequestData.hpp"

#include <string>

class IChatMessage
{
    public:
        virtual std::string BuildChatRequestMessage(IMessageBase& base, IChatRequestData& request) = 0;

        virtual bool ParseChatRequestMessage(std::string message, IChatRequestData& data) = 0;

};