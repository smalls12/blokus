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

        std::string GetLocalPlayerUniqueIdentifier() { return mLocalPlayerUniqueIdentifier; }

        bool GetPlayer(std::string uuid, std::shared_ptr<Player>& player);
        std::vector<std::shared_ptr<Player>> GetListOfPlayers() const;

        bool AddPlayerToGame(std::string uuid, std::shared_ptr<Player> player);
        bool AddLocalPlayerToGame(std::string uuid, std::shared_ptr<Player> player);

        bool RemovePlayerFromGame(std::string uuid);
        bool RemovePlayerFromGame(IRegistrationUnsuccessful& request);

        // used to handle responses to registration requests ( not the lobby host )
        bool RegisterPlayer(IRegistrationSuccessful& request);
        // used to handle responses to registration requests ( lobby host )
        bool RegisterPlayer(IRegisterRequest& request);

        friend std::ostream& operator <<(std::ostream& outputStream, const PlayerManager& playerManager);

    private:
        RegisterResponse&                                   mRegisterResponse;
        
        // keep track of the local player unique identifier
        // so it can be easily queried from the internal map structure
        std::string                                         mLocalPlayerUniqueIdentifier;

        std::map<std::string, std::shared_ptr<Player>>      mPlayers;
        mutable std::mutex                                  mPlayersMutex;
        
};