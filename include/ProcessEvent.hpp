#pragma once

#include "NetworkConnection.hpp"

class ProcessEvent
{
    public:
        ProcessEvent(NetworkConnection& connection);
        ~ProcessEvent();

    private:
        NetworkConnection& mConnection;
};