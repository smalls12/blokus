#pragma once

#include <string>

class IMessageProcessor
{
    public:
        virtual bool ProcessMessage(std::string data);

};