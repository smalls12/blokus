#include "BroadcastPlayerMove.hpp"

BroadcastPlayerMove::BroadcastPlayerMove(NetworkConnection& connection)
:   mConnection(connection)
{
    spdlog::get("console")->debug("BroadcastPlayerMove::BroadcastPlayerMove");

}

BroadcastPlayerMove::~BroadcastPlayerMove()
{
    spdlog::get("console")->debug("BroadcastPlayerMove::~BroadcastPlayerMove");

}