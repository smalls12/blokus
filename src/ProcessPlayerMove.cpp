#include "ProcessPlayerMove.hpp"

#include "spdlog/spdlog.h"

ProcessPlayerMove::ProcessPlayerMove(IGameLobby& lobby, IPlayerMoveRequest& request)
:   mLobby(lobby),
    mRequest(request)
{
    spdlog::get("console")->debug("ProcessPlayerMove::ProcessPlayerMove()");
}

ProcessPlayerMove::~ProcessPlayerMove()
{
    spdlog::get("console")->debug("ProcessPlayerMove::~ProcessPlayerMove()");
}

bool ProcessPlayerMove::Process(IPlayerMoveRequestData& data)
{
    spdlog::get("console")->debug("ProcessPlayerMove::Process() - Start");

    std::string message = mRequest.Build(data);
    mLobby.SendMessageToLobby( message );

    spdlog::get("console")->debug("ProcessPlayerMove::Process() - Done");

    return true;
}
