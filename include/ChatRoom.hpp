#pragma once

#include <list>
#include <string>

typedef std::pair<std::string, std::string> BlokusChatMessage;
typedef std::list<BlokusChatMessage> BlokusChatMessages;

class ChatRoom
{
    public:
        ChatRoom(unsigned int maxElements);
        ~ChatRoom();

        void AddMessage(std::string username, std::string message);
        BlokusChatMessages& GetMessages();

    private:
        unsigned int            mMaxElements;
        BlokusChatMessages      mMessages;
};