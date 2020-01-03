#pragma once

// protobuf header
#include <protobuf/blokus.pb.h>

#include "spdlog/spdlog.h"

class MessageProcessor
{
    public:
        MessageProcessor();
        ~MessageProcessor();

        bool ProcessMessage(std::string data);
        bool SetReceiveEndpoint(blokus::Type type, std::function<bool(blokus::Message, blokus::Message&)> func);
        bool SetResponseEndpoint(blokus::Type type, std::function<bool(blokus::Message)> func);

    private:
        bool ProcessRequest(blokus::Message in, blokus::Message& out);
        bool ProcessResponse(blokus::Message in);

        std::map<blokus::Type, std::function<bool(blokus::Message, blokus::Message&)>>            mReceiveEndpoints;
        std::map<blokus::Type, std::function<bool(blokus::Message)>>            mResponseEndpoints;
        std::mutex                                                              mEndpointsMutex;

};