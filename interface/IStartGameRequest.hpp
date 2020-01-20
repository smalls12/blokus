#pragma once

#include "IStartGameRequestData.hpp"

#include <string>

class IStartGameRequest
{
    public:
        virtual std::string Build(IStartGameRequestData& data) = 0;
};