#pragma once

#include "NetworkConnection.hpp"

#include "spdlog/spdlog.h"

class BroadcastPlayerMove
{
    public:
        BroadcastPlayerMove(NetworkConnection& connection);
        ~BroadcastPlayerMove();

        // overload function call
        void operator()(std::string message)
        {
            spdlog::get("console")->debug("BroadcastPlayerMove::operator() - Start");

            int rc = 0;
            std::string room = "BLOKUS";
            rc = zyre_shouts(mConnection.Get(), room.c_str(), "%s", message.c_str());

            spdlog::get("console")->debug("BroadcastPlayerMove::operator() - Done");

            return;
        }

    private:
        NetworkConnection&  mConnection;
};