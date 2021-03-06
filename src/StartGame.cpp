#include "StartGame.hpp"

#include "StartGameRequestData.hpp"

StartGame::StartGame(INetworkSend& send, IStartGameRequest& request)
:   mSend(send),
    mRequest(request)
{
    spdlog::get("console")->debug("StartGame::StartGame()");
}

StartGame::~StartGame()
{
    spdlog::get("console")->debug("StartGame::~StartGame()");
}

bool StartGame::Start(IGameSettings& settings, IPlayerRegistry& registry)
{
    spdlog::get("console")->debug("StartGame::Start() - Start");

    StartGameRequestData startGameRequestData;
    startGameRequestData.SetGameConfiguration(settings.GetGameConfiguration());
    std::vector<std::pair<std::string, PlayerId>> players;
    for( auto p : registry.GetListOfPlayers())
    {
        players.push_back(std::pair<std::string, PlayerId>(p->getUuid(), p->getPlayerId()));
    }
    startGameRequestData.SetPlayers(players);

    std::string message = mRequest.Build(startGameRequestData);
    mSend.Send( settings.GetGameName(), message );

    spdlog::get("console")->debug("StartGame::Start() - Done");

    return true;
}
