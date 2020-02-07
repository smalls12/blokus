#pragma once

#include <string>

class IChatRequestData
{
    public:

        virtual void SetUsername(std::string username) = 0;
        virtual std::string GetUsername() = 0;
        
        virtual void SetMessage(std::string message) = 0;
        virtual std::string GetMessage() = 0;
};