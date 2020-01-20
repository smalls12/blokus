#include "StartGameRequestData.hpp"

#include "spdlog/spdlog.h"

StartGameRequestData::StartGameRequestData()
{
    spdlog::get("console")->debug("StartGameRequestData::StartGameRequestData()");
}

StartGameRequestData::~StartGameRequestData()
{
    spdlog::get("console")->debug("StartGameRequestData::~StartGameRequestData()");
}