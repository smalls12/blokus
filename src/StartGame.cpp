#include "StartGame.hpp"

StartGame::StartGame(INetworkSend& send, IRequest& request)
:   mSend(send),
    mRequest(request)
{
    spdlog::get("console")->debug("StartGame::StartGame()");
}

StartGame::~StartGame()
{
    spdlog::get("console")->debug("StartGame::~StartGame()");
}

bool StartGame::Start(std::string gameName)
{
    spdlog::get("console")->debug("StartGame::Start() - Start");

    std::string message = mRequest.Build();
    mSend.Send( gameName, message );

    spdlog::get("console")->debug("StartGame::Start() - Done");

    return true;
}
