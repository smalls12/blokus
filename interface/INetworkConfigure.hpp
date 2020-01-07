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

class INetworkConfigure
{
    public:
        // Configure a network
        virtual bool Configure(std::string parameter) = 0;

        // Retrieve the name of the network
        virtual std::string GetName() = 0;

        // Retrieve the unique identifier of the network
        virtual std::string GetUniqueIdentifier() = 0;
};