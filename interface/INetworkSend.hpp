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

class INetworkSend
{
    public:
        // Send to the network
        virtual int Send(std::string groupName, std::string message) = 0;
};