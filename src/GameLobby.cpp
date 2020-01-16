#include "GameLobby.hpp"

GameLobby::GameLobby(IGameSettings& settings, INetworkSend& send)
:   mSettings(settings),
    mSend(send)
{
    spdlog::get("console")->debug("GameLobby::GameLobby()");
}

GameLobby::~GameLobby()
{
    spdlog::get("console")->debug("GameLobby::~GameLobby()");
}

bool GameLobby::SendMessageToLobby(std::string data)
{
    spdlog::get("console")->debug("GameLobby::SendMessageToLobby() - Start");

    mSend.Send( mSettings.GetGameName(), data );

    spdlog::get("console")->debug("GameLobby::SendMessageToLobby() - Done");

    return true;
}
