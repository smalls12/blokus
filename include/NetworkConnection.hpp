#pragma once

extern "C" {
// encapsulate zyre
#include "zyre.h"
}

#include <string>

class NetworkConnection
{
    public:
        NetworkConnection(std::string nodeName);
        ~NetworkConnection();

        zyre_t *Get();

    private:
        std::string     mNodeName;
        zyre_t          *mNode;
};