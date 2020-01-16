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

std::string StartGameRequest::Build()
{
    return mMessage.BuildStartGameRequestMessage(mBase);
}