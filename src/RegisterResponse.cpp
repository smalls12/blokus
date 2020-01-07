#include "RegisterResponse.hpp"

#include "spdlog/spdlog.h"

RegisterResponse::RegisterResponse(INetworkConfigure& config, INetworkSend& send, std::string username, std::string gameName, IRegisterMessage& message)
:   mConfig(config),
    mSend(send),
    mUsername(username),
    mGameName(gameName),
    mMessage(message)
{
    spdlog::get("console")->debug("RegisterResponse::RegisterResponse()");
}

RegisterResponse::~RegisterResponse()
{
    spdlog::get("console")->debug("RegisterResponse::~RegisterResponse()");
}

bool RegisterResponse::SendRegistrationSuccessfulResponse(IRegistrationSuccessful& successful)
{
    spdlog::get("console")->debug("RegisterResponse::SendRegistrationSuccessfulResponse() - Start");

    std::string message = mMessage.BuildRegistrationResponseMessage(successful);

    mSend.Send(mGameName, message);

    spdlog::get("console")->debug("RegisterResponse::SendRegistrationSuccessfulResponse() - Done");

    return true;
}

bool RegisterResponse::SendRegistrationUnsuccessfulResponse(IRegistrationUnsuccessful& unsuccessful)
{
    spdlog::get("console")->debug("RegisterResponse::SendRegistrationUnsuccessfulResponse() - Start");

    std::string message = mMessage.BuildRegistrationResponseMessage(unsuccessful);

    mSend.Send(mGameName, message);

    spdlog::get("console")->debug("RegisterResponse::SendRegistrationUnsuccessfulResponse() - Done");

    return true;
}