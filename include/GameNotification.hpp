#pragma once

#include "NotificationType.hpp"

#include "spdlog/spdlog.h"

class GameNotification
{
    public:
        GameNotification(std::string name, std::string uuid, NotificationType type, std::string data);
        ~GameNotification();

        std::string getName() { return mName; }
        std::string getUuid() { return mUuid; }
        NotificationType getType() { return mType; }
        std::string getData() { return mData; }

        friend std::ostream& operator <<(std::ostream& outputStream, const GameNotification& gm);

    private:
        std::string         mName;
        std::string         mUuid;
        NotificationType    mType;
        std::string         mData;
};