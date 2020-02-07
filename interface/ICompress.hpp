#pragma once

#include <string>

class ICompress
{
    public:
        virtual void Compress(std::string& input, std::string& output) = 0;
};