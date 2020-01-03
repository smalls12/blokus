#pragma once

/* ---------------------------------------------------------------
    ActiveGameManager.cpp

    Polls zyre to find active games.


--------------------------------------------------------------- */

#include "ActiveGame.hpp"

#include <vector>
#include <map>
#include <mutex>

class ActiveGameManager
{
    public:
        ActiveGameManager();
        ~ActiveGameManager();

        std::vector<std::shared_ptr<ActiveGame>> GetListOfActiveGames();
        bool GameAlreadyActive(std::string name, std::shared_ptr<ActiveGame> activeGame);
        bool AddActiveGame(std::string name, std::shared_ptr<ActiveGame> activeGame);
        bool RemoveActiveGame(std::string name);

    private:
        std::map<std::string, std::shared_ptr<ActiveGame>>      mActiveGames;
        std::mutex                                              mActiveGamesMutex;
        
};