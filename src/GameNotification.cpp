#include "GameNotification.hpp"
#include "NotificationTypeString.hpp"

GameNotification::GameNotification(std::string name, std::string uuid, NotificationType type, std::string data)
:   mName(name),
    mUuid(uuid),
    mType(type),
    mData(data)
{
    spdlog::get("console")->debug("GameNotification::GameNotification");
}

GameNotification::~GameNotification()
{
    spdlog::get("console")->debug("GameNotification::~GameNotification");
}

std::ostream& operator <<(std::ostream& outputStream, const GameNotification& gm)
{
    outputStream << "Name [ " << gm.mName << " ] - ";
    outputStream << "UUID [ " << gm.mUuid << " ] - ";
    outputStream << "Type [ " << NotificationTypeString::PrintNotificationTypeString(gm.mType) << " ] - ";
    outputStream << "Data [ " << gm.mData << " ]";
    return outputStream;
}