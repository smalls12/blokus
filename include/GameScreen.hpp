#pragma once

#include "IGameSettings.hpp"
#include "MessageProcessor.hpp"
#include "ReadGameNotification.hpp"
#include "PlayerManager.hpp"
#include "ProcessPlayerMove.hpp"

class GameScreen
{
    public:
        GameScreen( IGameSettings& settings,
                    MessageProcessor& messageProcessor,
                    ReadGameNotification& readGameNotification,
                    PlayerManager& playerManager,
                    ProcessPlayerMove& processPlayerMove   );
        ~GameScreen();

        bool ProcessRemotePlayerMove();
        bool Show();
    
    protected:
        IGameSettings&              mSettings;
        MessageProcessor&           mMessageProcessor;
        ReadGameNotification&       mReadGameNotification;
        PlayerManager&              mPlayerManager;
        ProcessPlayerMove&          mProcessPlayerMove;

    private:
        void InitializeGamePieces();
        void InitGame();
        bool ProcessPlayerMoveInternal();
        void UpdateGame();
        void DrawBoard();
        void DrawGamePieces();
        void DrawOverlayBoard();
        void DrawSelector();
        void DrawGame();
        void CheckForNotification();
        void UpdateDrawFrame();
        void UnloadGame();
};