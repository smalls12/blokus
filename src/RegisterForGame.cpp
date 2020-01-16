#include "RegisterForGame.hpp"

RegisterForGame::RegisterForGame(INetworkSend& send, IRegisterRequest& request, IRegisterMessage& message)
:   mSend(send),
    mRegisterRequest(request),
    mRegisterMessage(message)
{
    spdlog::get("console")->debug("RegisterForGame::RegisterForGame");
}

RegisterForGame::~RegisterForGame()
{
    spdlog::get("console")->debug("RegisterForGame::~RegisterForGame");
}

bool RegisterForGame::Register(std::string gameName)
{
    spdlog::get("console")->debug("RegisterForGame::Register() - Start");

    std::string message = mRegisterMessage.BuildRegistrationRequestMessage(mRegisterRequest);
    mSend.Send( gameName, message );

    spdlog::get("console")->debug("RegisterForGame::Register() - Done");

    return true;
}
