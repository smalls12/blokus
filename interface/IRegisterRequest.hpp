#pragma once

#include <string>

class IRegisterRequest
{
    public:

        virtual void SetUsername(std::string username) = 0;
        virtual std::string GetUsername() = 0;

        virtual void SetUuid(std::string uuid) = 0;
        virtual std::string GetUuid() = 0;
};