#pragma once

#include "IGameSettings.hpp"
#include "MessageProcessor.hpp"
#include "ReadGameNotification.hpp"
#include "PlayerManager.hpp"
#include "StartGame.hpp"

#include "GameLobbyScreen.hpp"

class StartGameLobbyScreen : public GameLobbyScreen
{
    public:
        StartGameLobbyScreen(   IGameSettings& settings,
                                MessageProcessor& messageProcessor,
                                ReadGameNotification& readGameNotification,
                                PlayerManager& playerManager,
                                StartGame& startGame    );
        ~StartGameLobbyScreen();

        bool ServerReadyToStart() { mReadyToStart = true; }

    private:     
        void UpdateReadyToStart();
        void DrawGameMode();
        void DrawReadyToStart();  
        
        bool mFourPlayerMode;
        bool mStartGameButton;

        StartGame&      mStartGame;
};