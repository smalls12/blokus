#pragma once

#include "INetworkConfigure.hpp"
#include "IMessageBase.hpp"

#include "spdlog/spdlog.h"

class MessageBase : public IMessageBase
{
    public:
        MessageBase(INetworkConfigure& config);
        ~MessageBase();

        std::string GetUniqueIdentifier() { return mConfig.GetUniqueIdentifier(); }

    private:
        INetworkConfigure&       mConfig;
};