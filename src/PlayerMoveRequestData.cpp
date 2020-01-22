#include "PlayerMoveRequestData.hpp"

#include "spdlog/spdlog.h"

PlayerMoveRequestData::PlayerMoveRequestData()
:   mPlayerId(PlayerId::UNASSIGNED)
{
    spdlog::get("console")->debug("PlayerMoveRequestData::PlayerMoveRequestData()");
}

PlayerMoveRequestData::~PlayerMoveRequestData()
{
    spdlog::get("console")->debug("PlayerMoveRequestData::~PlayerMoveRequestData()");
}