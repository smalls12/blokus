#pragma once

#include <string>

class IMessageBase
{
    public:
        // Retrieve the unique identifier of the network
        virtual std::string GetUniqueIdentifier() = 0;
};