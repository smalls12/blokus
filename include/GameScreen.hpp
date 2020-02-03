#pragma once

#include "IGameSettings.hpp"
#include "MessageProcessor.hpp"
#include "ReadGameNotification.hpp"
#include "PlayerManager.hpp"
#include "ProcessPlayerMove.hpp"
#include "PlayerTurnManager.hpp"
#include "InitialMoveIndicator.hpp"
#include "PlayerScores.hpp"

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
                    PlayerTurnManager& playerTurnManager,
                    InitialMoveIndicator& initialMoveIndicator,
                    PlayerScores& playerScores   );
        ~GameScreen();

        bool ProcessRemotePlayerMove(IPlayerMoveRequestData& data);
        bool Show();
    
    protected:
        IGameSettings&              mSettings;
        MessageProcessor&           mMessageProcessor;
        ReadGameNotification&       mReadGameNotification;
        PlayerManager&              mPlayerManager;
        ProcessPlayerMove&          mProcessPlayerMove;
        PlayerTurnManager&          mPlayerTurnManager;
        InitialMoveIndicator&       mInitialMoveIndicator;
        PlayerScores&               mPlayerScores;

    private:
        // private methods
        void InitializeGamePieces();
        void InitGame();
        bool ProcessPlayerMoveInternal();
        void UpdateGame();
        void DrawGamePieces();
        void DrawSelector();
        void DrawScores();
        void DrawGame();
        void CheckForNotification();
        void UpdateDrawFrame();
        void UnloadGame();

        // private variables
        GamePieceBank                       mGamePieceBank;
        PieceSelector                       mPieceSelector;
        PieceType                           mSelectedPieceType;
        PlayerSelectedPiece                 mPlayerSelectedPiece;

        std::pair<PlayerId, PlayerColor>    mCurrentPlayersTurn;
};