#pragma once

#include <string>

/* =========================================================
 *
 * Network layer abstraction
 * Building with reference to what I know I need from zyre
 * However should be abstract enough to replace with any
 * network technology
 * 
 * ========================================================= */

#include <string>

class INetworkLobby
{
    public:
        // Join a network lobby
        virtual bool JoinGroup(std::string groupName) = 0;

        // Leave a network lobby
        virtual bool LeaveGroup(std::string groupName) = 0;
};