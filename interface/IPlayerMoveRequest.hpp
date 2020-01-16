#pragma once

#include "IPlayerMoveRequestData.hpp"

#include <string>

class IPlayerMoveRequest
{
    public:
        virtual std::string Build(IPlayerMoveRequestData& data) = 0;
};