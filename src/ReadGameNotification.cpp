#include "ReadGameNotification.hpp"

ReadGameNotification::ReadGameNotification(NetworkConnection& connection, std::string gameName)
:   mConnection(connection),
    mGameName(gameName)
{
    // spdlog::get("console")->debug("ReadGameNotification::ReadGameNotification");
    SPDLOG_DEBUG("ReadGameNotification::ReadGameNotification() - Start");

    mPoller = zpoller_new(zyre_socket(mConnection.Get()), NULL);
}

ReadGameNotification::~ReadGameNotification()
{
    // spdlog::get("console")->debug("ReadGameNotification::~ReadGameNotification");
    SPDLOG_DEBUG("ReadGameNotification::~ReadGameNotification() - Start");
    
    zpoller_destroy(&mPoller);
}

bool ReadGameNotification::CheckEvent()
{
    // spdlog::get("console")->debug("ReadGameNotification::CheckEvent() - Start");
    SPDLOG_DEBUG("ReadGameNotification::CheckEvent() - Start");

    zsock_t *which = (zsock_t *)zpoller_wait(mPoller, 0);
    if( !which )
    {
        // spdlog::get("console")->debug("ReadGameNotification::operator() - No event.");
        SPDLOG_DEBUG("ReadGameNotification::CheckEvent() - No event.");
        return false;
    }

    // zpoller_expired
    // zpoller_terminated

    return true;
}