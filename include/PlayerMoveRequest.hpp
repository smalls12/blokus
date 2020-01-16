#pragma once

/* =========================================================
 *
 * PlayerMoveRequest.hpp
 * 
 * Concrete implementation for building the player move request
 * 
 * The player move message requries IMessageBase for the UUID
 * The player move message will be built using the IPlayerMoveMessage
 * The player move message requires meta data from IPlayerMoveRequest
 * 
 * ========================================================= */

#include "IRequest.hpp"
#include "IPlayerMoveMessage.hpp"
#include "IMessageBase.hpp"
#include "IPlayerMoveRequest.hpp"
#include "IPlayerMoveRequestData.hpp"

class PlayerMoveRequest : public IPlayerMoveRequest
{
    public:
        PlayerMoveRequest(IPlayerMoveMessage& message, IMessageBase& base);
        ~PlayerMoveRequest();

        std::string Build(IPlayerMoveRequestData& data);

    private:
        IPlayerMoveMessage&     mMessage;
        IMessageBase&           mBase;
};