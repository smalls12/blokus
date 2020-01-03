#include "WaitForServerNode.hpp"

WaitForServerNode::WaitForServerNode(ReadGameNotification& readGameNotification, Game game)
:   mReadGameNotification(readGameNotification),
    mGame(game)
{
    spdlog::get("console")->info("WaitForServerNode::WaitForServerNode");

}

WaitForServerNode::~WaitForServerNode()
{
    spdlog::get("console")->info("WaitForServerNode::~WaitForServerNode");

}