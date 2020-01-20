#pragma once

/* ---------------------------------------------------------------
    PlayerManager.hpp

    Polls zyre to find active games.


--------------------------------------------------------------- */
 
#include "IPlayerRegistry.hpp"
#include "RegisterResponse.hpp"
#include "Player.hpp"

#include <vector>
#include <map>
#include <mutex>
#include <memory>

class PlayerManager : public IPlayerRegistry
{
    public:
        PlayerManager(RegisterResponse& registerResponse);
        ~PlayerManager();

        bool GetPlayer(std::string uuid, std::shared_ptr<Player>& player);
        std::vector<std::shared_ptr<Player>> GetListOfPlayers();
        bool AddPlayerToGame(std::string uuid, std::shared_ptr<Player> player);
        bool RemovePlayerFromGame(std::string uuid);
        bool RemovePlayerFromGame(IRegistrationUnsuccessful& request);

        bool RegisterLocalPlayer(IRegistrationSuccessful& request);
        bool RegisterRemotePlayer(IRegisterRequest& request);

    private:
        RegisterResponse&                                   mRegisterResponse;
        
        std::map<std::string, std::shared_ptr<Player>>      mPlayers;
        std::mutex                                          mPlayersMutex;
        
};