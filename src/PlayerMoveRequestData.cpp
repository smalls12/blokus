#include "PlayerMoveRequestData.hpp"

#include "spdlog/spdlog.h"

PlayerMoveRequestData::PlayerMoveRequestData()
:   mPlayerId(PlayerId::PLAYER_ONE)
{
    spdlog::get("console")->debug("PlayerMoveRequestData::PlayerMoveRequestData()");
}

PlayerMoveRequestData::~PlayerMoveRequestData()
{
    spdlog::get("console")->debug("PlayerMoveRequestData::~PlayerMoveRequestData()");
}