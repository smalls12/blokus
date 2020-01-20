#pragma once

#include "IGameSettings.hpp"
#include "MessageProcessor.hpp"
#include "ReadGameNotification.hpp"
#include "PlayerManager.hpp"
#include "StartGame.hpp"
#include "IRandomizePlayerIds.hpp"

#include "GameLobbyScreen.hpp"

class StartGameLobbyScreen : public GameLobbyScreen
{
    public:
        StartGameLobbyScreen(   IGameSettings& settings,
                                MessageProcessor& messageProcessor,
                                ReadGameNotification& readGameNotification,
                                PlayerManager& playerManager,
                                StartGame& startGame,
                                IRandomizePlayerIds& randomizePlayerIds);
        ~StartGameLobbyScreen();

        bool ServerReadyToStart() { mReadyToStart = true; }

    private:     
        void UpdateReadyToStart();
        void DrawGameMode();
        void DrawReadyToStart();  
        
        bool mFourPlayerMode;
        bool mStartGameButton;

        StartGame&              mStartGame;
        IRandomizePlayerIds&    mRandomizePlayerIds;
};