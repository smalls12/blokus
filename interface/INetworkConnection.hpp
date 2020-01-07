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

class INetworkConnection
{
    public:
        // Connect into the network
        virtual bool Connect() = 0;

        // Disconnect from the network
        virtual void Disconnect() = 0;

        // Represents any steps required after connecting
        virtual bool Start() = 0;

        // Represents any steps required prior to disconnecting
        virtual void Stop() = 0;
};