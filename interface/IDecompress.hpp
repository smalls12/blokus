#pragma once

#include <string>

class IDecompress
{
    public:
        virtual void Decompress(std::string& input, std::string& output) = 0;
};