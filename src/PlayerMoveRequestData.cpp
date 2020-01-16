#include "PlayerMoveRequestData.hpp"

#include "spdlog/spdlog.h"

PlayerMoveRequestData::PlayerMoveRequestData()
{
    spdlog::get("console")->debug("PlayerMoveRequestData::PlayePlayerMoveRequestDatarMoveRequest()");
}

PlayerMoveRequestData::~PlayerMoveRequestData()
{
    spdlog::get("console")->debug("PlayerMoveRequestData::~PlayerMoveRequestData()");
}