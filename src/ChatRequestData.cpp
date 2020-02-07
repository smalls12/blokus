#include "ChatRequestData.hpp"

#include "spdlog/spdlog.h"

ChatRequestData::ChatRequestData()
:   mUsername(),
    mMessage()
{
    spdlog::get("console")->debug("ChatRequestData::ChatRequestData()");
}

ChatRequestData::~ChatRequestData()
{
    spdlog::get("console")->debug("ChatRequestData::~ChatRequestData()");
}