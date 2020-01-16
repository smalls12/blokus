#include "PlayerMoveRequest.hpp"

#include "spdlog/spdlog.h"

PlayerMoveRequest::PlayerMoveRequest(IPlayerMoveMessage& message, IMessageBase& base)
:   mMessage(message),
    mBase(base)
{
    spdlog::get("console")->debug("PlayerMoveRequest::PlayerMoveRequest()");
}

PlayerMoveRequest::~PlayerMoveRequest()
{
    spdlog::get("console")->debug("PlayerMoveRequest::~PlayerMoveRequest()");
}

std::string PlayerMoveRequest::Build(IPlayerMoveRequestData& data)
{
    return mMessage.BuildPlayerMoveRequestMessage(mBase, data);
}