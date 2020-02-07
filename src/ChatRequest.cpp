#include "ChatRequest.hpp"

#include "spdlog/spdlog.h"

ChatRequest::ChatRequest(IChatMessage& message, IMessageBase& base)
:   mMessage(message),
    mBase(base)
{
    spdlog::get("console")->debug("ChatRequest::ChatRequest()");
}

ChatRequest::~ChatRequest()
{
    spdlog::get("console")->debug("ChatRequest::~ChatRequest()");
}

std::string ChatRequest::Build(IChatRequestData& data)
{
    return mMessage.BuildChatRequestMessage(mBase, data);
}