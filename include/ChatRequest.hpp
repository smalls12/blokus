#pragma once

/* =========================================================
 *
 * ChatRequest.hpp
 * 
 * Concrete implementation for building a chat request
 * 
 * The player move message requries IMessageBase for the UUID
 * The player move message will be built using the IChatMessage
 * The player move message requires meta data from IChatRequest
 * 
 * ========================================================= */

#include "IChatMessage.hpp"
#include "IMessageBase.hpp"
#include "IChatRequest.hpp"
#include "IChatRequestData.hpp"

class ChatRequest : public IChatRequest
{
    public:
        ChatRequest(IChatMessage& message, IMessageBase& base);
        ~ChatRequest();

        std::string Build(IChatRequestData& data);

    private:
        IChatMessage&           mMessage;
        IMessageBase&           mBase;
};