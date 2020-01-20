#include "StartGameRequest.hpp"

StartGameRequest::StartGameRequest(IStartGameMessage& message, IMessageBase& base)
:   mMessage(message),
    mBase(base)
{
    spdlog::get("console")->debug("StartGameRequest::StartGameRequest()");
}

StartGameRequest::~StartGameRequest()
{
    spdlog::get("console")->debug("StartGameRequest::~StartGameRequest()");
}

std::string StartGameRequest::Build(IStartGameRequestData& data)
{
    return mMessage.BuildStartGameRequestMessage(mBase, data);
}