#pragma once

#include <string>

class IRequest
{
    public:
        virtual std::string Build() = 0;
};