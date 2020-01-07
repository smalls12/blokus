#include "ReadGameNotification.hpp"

ReadGameNotification::ReadGameNotification(INetworkReceive& receive, std::string gameName)
:   mReceive(receive),
    mGameName(gameName)
{
    spdlog::get("console")->debug("ReadGameNotification::ReadGameNotification()");
}

ReadGameNotification::~ReadGameNotification()
{
    spdlog::get("console")->debug("ReadGameNotification::~ReadGameNotification()");
}

bool ReadGameNotification::CheckEvent()
{
    spdlog::get("console")->debug("ReadGameNotification::CheckEvent() - Start");
    return mReceive.Poll();
}

bool ReadGameNotification::Receive(GameNotification& gm)
{
    spdlog::get("console")->trace("ReadGameNotification::Receive() - Start");

    std::vector<std::string> message;
    if( mReceive.Receive(mGameName, message) )
    {
        NotificationType nt = NotificationType::UNKNOWN;
        if (message[2] == "JOIN")
        {
            nt = NotificationType::JOIN;
        }
        else if (message[2] == "LEAVE")
        {
            nt = NotificationType::LEAVE;
        }
        else if (message[2] == "SHOUT")
        {
            nt = NotificationType::MESSAGE;
        }
        else if (message[2] == "WHISPER")
        {
            nt = NotificationType::MESSAGE;
        }
        else if (message[2] == "EVASIVE")
        {
            nt = NotificationType::EVASIVE;
        }
        else if (message[2] == "SILENT")
        {
            nt = NotificationType::SILENT;
        }
        else
        {
            spdlog::get("console")->warn("ReadGameNotification::Receive() - Event not handled.");
        }

        gm = GameNotification(message[0], message[1], nt, message[3]);
        return true;
    }
    else
    {
        return false;
    }
}