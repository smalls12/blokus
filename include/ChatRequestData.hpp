#pragma once

/* =========================================================
 *
 * ChatRequestData.hpp
 * 
 * Concrete implementation for that data to build the
 * chat request
 * 
 * ========================================================= */

#include "IChatRequestData.hpp"

class ChatRequestData : public IChatRequestData
{
    public:
        ChatRequestData();
        ~ChatRequestData();

        void SetUsername(std::string username) { mUsername = username; }
        std::string GetUsername() { return mUsername; }

        void SetMessage(std::string message) { mMessage = message; }
        std::string GetMessage() { return mMessage; }

    private:
        std::string     mUsername;
        std::string     mMessage;
};