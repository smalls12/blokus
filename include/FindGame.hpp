#pragma once

/*
 * ===================================================================
 * FindGame.hpp
 * 
 * Used to find active games of blokus
 * 
 * To identify active game of blokus, search all peers for the
 * X-BLOKUS header
 * 
 * The X-BLOKUS header is published by the node that has started
 * a game of Blokus
 * ===================================================================
 */

#include "INetworkSearch.hpp"
#include "ActiveGameManager.hpp"

#include "spdlog/spdlog.h"

#include <memory>

class FindGame
{
    public:
        FindGame(INetworkSearch& search, ActiveGameManager& activeGameManager);
        ~FindGame();

        // overload function call
        void operator()()
        {
            spdlog::get("console")->trace("FindGame::operator() - Start");

            std::vector<std::pair<std::string, std::string>> lobbies;
            mSearch.Search(lobbies);
            for(auto const& lobby: lobbies)
            {
                std::shared_ptr<ActiveGame> ag;
                if( !mActiveGameManager.GameAlreadyActive(lobby.first, ag) )
                {
                    ag = std::make_shared<ActiveGame>(std::string(lobby.first), std::string(lobby.second));
                    mActiveGameManager.AddActiveGame(std::string(lobby.first), ag);
                }
            }

            spdlog::get("console")->trace("FindGame::operator() - Done");

            return;
        }

    private:
        INetworkSearch&     mSearch;
        ActiveGameManager&  mActiveGameManager;
};