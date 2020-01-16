#include "MessageBase.hpp"

#include "spdlog/spdlog.h"

MessageBase::MessageBase(INetworkConfigure& config)
:   mConfig(config)
{
    spdlog::get("console")->debug("MessageBase::MessageBase()");
}

MessageBase::~MessageBase()
{
    spdlog::get("console")->debug("MessageBase::~MessageBase()");
}