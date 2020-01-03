#pragma once

/*
 * ===================================================================
 * WaitForServerNode.hpp
 * 
 * Once a client node has joined the lobby, it will take a few
 * seconds for it to find the other nodes in the lobby.
 * 
 * The server needs to be present before the clients before we
 * register to it.
 * ===================================================================
 */

#include "ReadGameNotification.hpp"
#include "Game.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

class WaitForServerNode
{
    public:
        WaitForServerNode(ReadGameNotification& readGameNotification, Game game);
        ~WaitForServerNode();

        // overload function call
        bool operator()()
        {
            spdlog::get("console")->trace("WaitForServerNode::operator() - Start");

            while( true )
            {
                if( mReadGameNotification.CheckEvent() )
                {
                    GameNotification gn = mReadGameNotification();
                    std::stringstream ss;
                    ss << gn;
                    spdlog::get("console")->error("WaitForServerNode::operator() - Received notification [ {} ]", ss.str());

                    switch(gn.getType())
                    {
                        case NotificationType::JOIN:
                        {
                            spdlog::get("console")->debug("WaitForServerNode::operator() - Server located @ [ {} ]", mGame.GetServer());

                            if( gn.getUuid() == mGame.GetServer() )
                            {
                                spdlog::get("console")->error("WaitForServerNode::operator() - Server joined!");
                                return true;
                            }
                            break;
                        }
                        default:
                        {
                            spdlog::get("console")->error("WaitForServerNode::operator() - Unknown notification [ {} ]");
                            break;
                        }
                    }
                }
            }

            spdlog::get("console")->trace("WaitForServerNode::operator() - Done");

            return false;
        }

    private:
        ReadGameNotification&   mReadGameNotification;
        Game&                   mGame;
};