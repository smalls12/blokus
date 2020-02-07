#include "ChatRoom.hpp"

#include "spdlog/spdlog.h"

ChatRoom::ChatRoom(unsigned int maxElements)
:   mMaxElements(maxElements),
    mMessages()
{
    spdlog::get("console")->debug("ChatRoom::ChatRoom()");
}

ChatRoom::~ChatRoom()
{
    spdlog::get("console")->debug("ChatRoom::~ChatRoom()");
}

void ChatRoom::AddMessage(std::string username, std::string message)
{
    spdlog::get("console")->debug("ChatRoom::AddMessage() - Start");

    if( mMessages.size() >= mMaxElements)
    {
        mMessages.pop_front();
    }
    mMessages.push_back(BlokusChatMessage{username, message});
}

BlokusChatMessages& ChatRoom::GetMessages()
{
    spdlog::get("console")->trace("ChatRoom::GetMessages() - Start");
    return mMessages;
}