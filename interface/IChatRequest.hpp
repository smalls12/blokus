#pragma once

#include "IChatRequestData.hpp"

#include <string>

class IChatRequest
{
    public:
        virtual std::string Build(IChatRequestData& data) = 0;
};