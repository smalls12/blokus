#pragma once

#include "GameNotification.hpp"

/* =========================================================
 *
 * Network layer abstraction
 * Building with reference to what I know I need from zyre
 * However should be abstract enough to replace with any
 * network technology
 * 
 * ========================================================= */

class INetworkReceive
{
    public:
        // Poll for events
        virtual bool Poll() = 0;

        // Receive from the network
        virtual bool Receive(std::string groupName, std::vector<std::string>& messages) = 0;
};