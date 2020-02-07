#include "ProcessChatMessage.hpp"

#include "spdlog/spdlog.h"

ProcessChatMessage::ProcessChatMessage(IGameLobby& lobby, IChatRequest& request)
:   mLobby(lobby),
    mRequest(request)
{
    spdlog::get("console")->debug("ProcessChatMessage::ProcessChatMessage()");
}

ProcessChatMessage::~ProcessChatMessage()
{
    spdlog::get("console")->debug("ProcessChatMessage::~ProcessChatMessage()");
}

bool ProcessChatMessage::Process(IChatRequestData& data)
{
    spdlog::get("console")->debug("ProcessChatMessage::Process() - Start");

    std::string message = mRequest.Build(data);
    mLobby.SendMessageToLobby( message );

    spdlog::get("console")->debug("ProcessChatMessage::Process() - Done");

    return true;
}
