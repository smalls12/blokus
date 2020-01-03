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

#include "NetworkConnection.hpp"
#include "ActiveGameManager.hpp"

#include "spdlog/spdlog.h"

#include <memory>

class FindGame
{
    public:
        FindGame(NetworkConnection& connection, ActiveGameManager& activeGameManager);
        ~FindGame();

        // overload function call
        void operator()()
        {
            spdlog::get("console")->trace("FindGame::operator() - Start");

            // Debug();

            zlist_t* peers = zyre_peers(mConnection.Get());
            while(zlist_size(peers) > 0)
            {
                char *uuid;
                uuid = (char *)zlist_pop (peers);
                spdlog::get("console")->trace("FindGame::operator() - Peer {}", uuid);

                char *value = zyre_peer_header_value(mConnection.Get(), uuid, "X-BLOKUS");
                if( value )
                {
                    std::string header(value);
                    zstr_free(&value);
                    spdlog::get("console")->trace("FindGame::operator() - Header Value {}", header);

                    std::shared_ptr<ActiveGame> ag;
                    if( !mActiveGameManager.GameAlreadyActive(header, ag) )
                    {
                        ag = std::make_shared<ActiveGame>(std::string(header), std::string(uuid));
                        mActiveGameManager.AddActiveGame(std::string(header), ag);
                    }
                }
            }
            zlist_destroy (&peers);         

            spdlog::get("console")->trace("FindGame::operator() - Done");

            return;
        }

        inline void Debug()
        {
            zyre_print(mConnection.Get());
        }

        inline void FindPeers()
        {
            // zlist_t* peers = zyre_peers(mConnection.Get());
            // while(zlist_size(peers) > 0)
            // {
            //     char *item;
            //     item = (char *) zlist_pop (peers);
            //     spdlog::get("console")->info("FindGame::operator() - Peer {}", item);
   
            // }
            // zlist_destroy (&peers);
        }

        inline void FindGroups()
        {
            // find games
            // zlist_t* games = zyre_peer_groups(mConnection.Get());
            // while(zlist_size(games) > 0)
            // {
            //     char *game;
            //     game = (char *)zlist_pop(games);
            //     spdlog::get("console")->debug("FindGame::operator() - Peer Group {}", game);

            //     zlist_t* peers_in_game = zyre_peers_by_group(mConnection.Get(), game);
            //     // are there people already in the game ?
            //     if( zlist_size(peers_in_game) > 0 )
            //     {
            //         spdlog::get("console")->info("FindGame::operator() - Peers in Group");

            //         std::shared_ptr<ActiveGame> ag;
            //         if( !mActiveGameManager.GameAlreadyActive(game, ag) )
            //         {
            //             ag = std::make_shared<ActiveGame>(std::string(game));
            //             mActiveGameManager.AddActiveGame(std::string(game), ag);
            //         }
                    
            //         while(zlist_size(peers_in_game) > 0)
            //         {
            //             char *peer_in_game;
            //             peer_in_game = (char *)zlist_pop(peers_in_game);
            //             if(ag)
            //             {
            //                 ag->AddPeerToGame(std::string(peer_in_game));
            //             }
            //         }
            //     }
            //     else
            //     {
            //         spdlog::get("console")->debug("FindGame::operator() - No Peers in Group");
            //     }
            //     zlist_destroy(&peers_in_game);
            // }
            // zlist_destroy(&games);
        }

    private:
        NetworkConnection&  mConnection;
        ActiveGameManager&  mActiveGameManager;
};