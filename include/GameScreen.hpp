#pragma once

#include "IGameSettings.hpp"
#include "MessageProcessor.hpp"
#include "ReadGameNotification.hpp"
#include "PlayerManager.hpp"
#include "ProcessPlayerMove.hpp"
#include "GameFlowManager.hpp"

#include "IPlayerMoveRequestData.hpp"

#include "GamePieceBank.hpp"
#include "PieceSelector.hpp"
#include "PlayerSelectedPiece.hpp"

class GameScreen
{
    public:
        GameScreen( IGameSettings& settings,
                    MessageProcessor& messageProcessor,
                    ReadGameNotification& readGameNotification,
                    PlayerManager& playerManager,
                    ProcessPlayerMove& processPlayerMove,
                    GameFlowManager& gameFlowManager   );
        ~GameScreen();

        bool ProcessRemotePlayerMove(IPlayerMoveRequestData& data);
        bool Show();
    
    protected:
        IGameSettings&              mSettings;
        MessageProcessor&           mMessageProcessor;
        ReadGameNotification&       mReadGameNotification;
        PlayerManager&              mPlayerManager;
        ProcessPlayerMove&          mProcessPlayerMove;
        GameFlowManager&            mGameFlowManager;

    private:
        // private methods
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

        // private variables
        GamePieceBank           mGamePieceBank;
        PieceSelector           mPieceSelector;
        PieceType               mSelectedPieceType;
        PlayerSelectedPiece     mPlayerSelectedPiece;
};