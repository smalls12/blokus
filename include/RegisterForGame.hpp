#pragma once

#include "NetworkConnection.hpp"
#include "Message.hpp"

#include "spdlog/spdlog.h"

class RegisterForGame
{
    public:
        RegisterForGame(NetworkConnection& connection, std::string gameName);
        ~RegisterForGame();

        // overload function call
        void operator()(std::string username, std::string uuid)
        {
            spdlog::get("console")->debug("RegisterForGame::operator() - Start");

            // build message
            blokus::Message _register = Message::BuildRegisterReq(username, uuid);

            // send to server
            // serialize the protobuf message
            size_t size = _register.ByteSizeLong(); 
            void *buffer = malloc(size);
            _register.SerializeToArray(buffer, size);

            int rc = 0;
            rc = zyre_shouts(mConnection.Get(), mGameName.c_str(), "%s", (char *)buffer);

            spdlog::get("console")->debug("RegisterForGame::operator() - Done");

            return;
        }

    private:
        NetworkConnection&  mConnection;
        std::string         mGameName;
};