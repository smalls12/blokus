#pragma once

/* ---------------------------------------------------------------
    PlayerManager.hpp

    Polls zyre to find active games.


--------------------------------------------------------------- */

// protobuf header
#include <protobuf/blokus.pb.h>

#include "Player.hpp"

#include <vector>
#include <map>
#include <mutex>
#include <memory>

class PlayerManager
{
    public:
        PlayerManager();
        ~PlayerManager();

        bool GetPlayer(std::string uuid, std::shared_ptr<Player>& player);
        std::vector<std::shared_ptr<Player>> GetListOfPlayers();
        bool AddPlayerToGame(std::string uuid, std::shared_ptr<Player> player);
        bool RemovePlayerFromGame(std::string uuid);

        bool RegisterPlayer(blokus::Message in);
        bool RegisterPlayer(blokus::Message in, blokus::Message& out);

    private:
        std::map<std::string, std::shared_ptr<Player>>      mPlayers;
        std::mutex                                          mPlayersMutex;
        
};