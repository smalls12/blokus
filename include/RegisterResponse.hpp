#pragma once

#include "NetworkConnection.hpp"
#include "Message.hpp"

#include "spdlog/spdlog.h"

class RegisterResponse
{
    public:
        RegisterResponse(NetworkConnection& connection, std::string username, std::string gameName);
        ~RegisterResponse();

        // overload function call
        void operator()(std::string username)
        {
            
        }

        bool SendRegisterResponse(blokus::Message message);

    private:
        NetworkConnection&  mConnection;
        std::string         mUsername;
        std::string         mGameName;
};