#define BOARD_SQUARE_SIZE       20
#define PIECE_SQUARE_SIZE       10

#define GRID_HORIZONTAL_SIZE    20
#define GRID_VERTICAL_SIZE      20

#include "ValidateMove.hpp"

#include "GridSquare.hpp"
#include "Point.hpp"
#include "Layout.hpp"

#include "Piece.hpp"
#include "PieceTypeString.hpp"

#include "AddPiece.hpp"
#include "ClearBoard.hpp"
#include "MergeBoards.hpp"

#include "CheckBoundaries.hpp"

#include "GameBoard.hpp"
#include "OverlayBoard.hpp"

#include "GameScreen.hpp"

#include "PlayerMoveRequestData.hpp"

#include "PieceTypeIterator.hpp"

#include "PiecesAvailableForPlayLocations.hpp"

#include "PlayerIdString.hpp"

extern "C" {
#include "raylib.h"
}

namespace
{
    static const int screenWidth = 600;
    static const int screenHeight = 600;

    static bool gameOver = false;
    static bool pause = false;

    GameBoard gb;
    OverlayBoard overlayBoard;

    static bool selected = false;
    static Point selectedPieceLocation = Point(0,0);

    static bool beginPlay = true;

    static PlayerId currentPlayersTurn = PlayerId::PLAYER_ONE;
}

#include "DrawBoard.hpp"
#include "DrawPiecesOnBoard.hpp"

GameScreen::GameScreen(IGameSettings& settings,
                       MessageProcessor& messageProcessor,
                       ReadGameNotification& readGameNotification,
                       PlayerManager& playerManager,
                       ProcessPlayerMove& processPlayerMove,
                       GameFlowManager& gameFlowManager )
:   mSettings(settings),
    mMessageProcessor(messageProcessor),
    mReadGameNotification(readGameNotification),
    mPlayerManager(playerManager),
    mProcessPlayerMove(processPlayerMove),
    mGameFlowManager(gameFlowManager),
    mGamePieceBank(),
    mPieceSelector(),
    mSelectedPieceType(mPieceSelector.GetNextPiece()),
    //mSelectedPiece(nullptr)
    mPlayerSelectedPiece(nullptr)
{
    spdlog::get("console")->info("GameScreen::GameScreen() - Start");

    std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
    std::shared_ptr<Player> player;
    mPlayerManager.GetPlayer(uuid, player);

    // mSelectedPiece = mGamePieceBank.GetPlayerPiece(player->getPlayerId(), mSelectedPieceType);
    mPlayerSelectedPiece = PlayerSelectedPiece(mGamePieceBank.GetPlayerPiece(player->getPlayerId(), mSelectedPieceType));
}

GameScreen::~GameScreen()
{
    spdlog::get("console")->info("GameScreen::~GameScreen() - Start");
}

// Initialize game variables
void GameScreen::InitGame(void)
{
    pause = false;

    beginPlay = true;

    ClearBoard::EmptyBoard( gb );
    ClearBoard::EmptyBoard( overlayBoard );
}

bool GameScreen::ProcessPlayerMoveInternal()
{
    spdlog::get("console")->info("GameScreen::ProcessPlayerMoveInternal() - Start");

    if ( ValidateMove::Validate( gb, overlayBoard ) )
    {
        MergeBoards::Merge(gb, overlayBoard);

        std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
        std::shared_ptr<Player> player;
        mPlayerManager.GetPlayer(uuid, player);

        PlayerMoveRequestData playerMoveRequestData;
        playerMoveRequestData.SetPlayerId(player->getPlayerId());
        playerMoveRequestData.SetPieceType(mSelectedPieceType);
        playerMoveRequestData.SetLocation(selectedPieceLocation);

        mProcessPlayerMove.Process(playerMoveRequestData);

        return true;
    }
    else
    {
        spdlog::get("console")->error("GameScreen::ProcessPlayerMoveInternal() - Invalid location.");
        return false;
    }
}

bool GameScreen::ProcessRemotePlayerMove(IPlayerMoveRequestData& data)
{
    spdlog::get("console")->info("GameScreen::ProcessRemotePlayerMove() - Start");

    AddPiece::AddPieceToBoard( gb, *mGamePieceBank.GetPlayerPiece(data.GetPlayerId(), data.GetPieceType()), data.GetLocation() );

    // advance to next player
    currentPlayersTurn = mGameFlowManager.NextPlayersTurn();

    return true;
}

// Update game (one frame)
void GameScreen::UpdateGame(void)
{
    if (!gameOver)
    {
        if ( IsKeyPressed('P') )
        {
            pause = !pause;
        }

        std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
        std::shared_ptr<Player> player;
        mPlayerManager.GetPlayer(uuid, player);

        if (!pause && ( currentPlayersTurn == player->getPlayerId() ))
        {
            if( selected )
            {
                if ( IsKeyPressed(KEY_ESCAPE) )
                {
                    selected = false;
                }

                if ( IsKeyPressed(KEY_LEFT) )
                {
                    selectedPieceLocation = overlayBoard.MovePiece(MovementDirection::LEFT);
                }

                if ( IsKeyPressed(KEY_RIGHT) )
                {
                    selectedPieceLocation = overlayBoard.MovePiece(MovementDirection::RIGHT);
                }

                if ( IsKeyPressed(KEY_UP) )
                {
                    selectedPieceLocation =overlayBoard.MovePiece(MovementDirection::UP);
                }

                if ( IsKeyPressed(KEY_DOWN) )
                {
                    selectedPieceLocation = overlayBoard.MovePiece(MovementDirection::DOWN);
                }

                if ( IsKeyPressed(KEY_ENTER) )
                {
                    if ( ProcessPlayerMoveInternal() )
                    {
                        // piece has been played, make piece unavailable to be played again
                        mPlayerSelectedPiece.GetPiece()->PiecePlayed();

                        // advance to next player
                        currentPlayersTurn = mGameFlowManager.NextPlayersTurn();

                        selected = false;
                    }
                }
            }
            else
            {
                if ( IsKeyPressed(KEY_SPACE) )
                {
                    std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
                    std::shared_ptr<Player> player;
                    mPlayerManager.GetPlayer(uuid, player);

                    do
                    {
                        mSelectedPieceType = mPieceSelector.GetNextPiece();
                    }
                    while( mGamePieceBank.GetPlayerPiece(player->getPlayerId(), mSelectedPieceType)->HasPieceBeenPlayed() );

                    spdlog::get("console")->info("GameScreen::UpdateGame() - {} Piece Selected", PieceTypeString::PrintPieceTypeString(mSelectedPieceType));
                }

                if ( IsKeyPressed(KEY_ENTER) )
                {
                    std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
                    std::shared_ptr<Player> player;
                    mPlayerManager.GetPlayer(uuid, player);

                    mPlayerSelectedPiece = PlayerSelectedPiece(mGamePieceBank.GetPlayerPiece(player->getPlayerId(), mSelectedPieceType));
                    
                    overlayBoard.SetSelectedGamePiece( Piece( mPlayerSelectedPiece.GetPiece()->GetLayout() ) );

                    selected = true;
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

void GameScreen::DrawGamePieces()
{
    PiecesAvailableForPlayLocations locations;
    for (std::map<PieceType, const Point>::const_iterator it = locations.cbegin(); it != locations.cend(); ++it)
    {
        Vector2 pieceOffset;

        pieceOffset.x = it->second.GetX();
        pieceOffset.y = it->second.GetY();

        int controller = pieceOffset.x;

        std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
        std::shared_ptr<Player> player;
        mPlayerManager.GetPlayer(uuid, player);

        PlayerSelectedPiece piece(mGamePieceBank.GetPlayerPiece(player->getPlayerId(), it->first));

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                switch( piece.GetPiece()->GetLayout().Get(i, j) )
                {
                    case GridSquare::EMPTY:
                    {
                        if( piece.GetPiece()->HasPieceBeenPlayed() )
                        {
                            DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, BLACK);
                        }
                        else
                        {
                            DrawLine(pieceOffset.x, pieceOffset.y, pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y, LIGHTGRAY );
                            DrawLine(pieceOffset.x, pieceOffset.y, pieceOffset.x, pieceOffset.y + PIECE_SQUARE_SIZE, LIGHTGRAY );
                            DrawLine(pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y, pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y + PIECE_SQUARE_SIZE, LIGHTGRAY );
                            DrawLine(pieceOffset.x, pieceOffset.y + PIECE_SQUARE_SIZE, pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y + PIECE_SQUARE_SIZE, LIGHTGRAY );
                        }
                        break;
                    }
                    case GridSquare::BLOCK:
                    {
                        break;
                    }
                    case GridSquare::PLAYER_ONE:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, BLUE);
                        break;
                    }
                    case GridSquare::PLAYER_TWO:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, RED);
                        break;
                    }
                    case GridSquare::PLAYER_THREE:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, YELLOW);
                        break;
                    }
                    case GridSquare::PLAYER_FOUR:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, GREEN);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                pieceOffset.x += PIECE_SQUARE_SIZE;
            }

            pieceOffset.x = controller;
            pieceOffset.y += PIECE_SQUARE_SIZE;
        }
    }
}

void GameScreen::DrawSelector()
{
    PiecesAvailableForPlayLocations locations;

    Vector2 selectorOffset;

    selectorOffset.x = locations.GetPieceLocation(mSelectedPieceType).GetX();
    selectorOffset.y = locations.GetPieceLocation(mSelectedPieceType).GetY();

    // draw the piece selector
    DrawLine(selectorOffset.x, selectorOffset.y, selectorOffset.x + ( PIECE_SQUARE_SIZE * 5 ), selectorOffset.y + 1, DARKGRAY );
    DrawLine(selectorOffset.x, selectorOffset.y, selectorOffset.x + 1, selectorOffset.y + ( PIECE_SQUARE_SIZE * 5 ), DARKGRAY );
    DrawLine(selectorOffset.x + ( PIECE_SQUARE_SIZE * 5 ), selectorOffset.y, selectorOffset.x + ( PIECE_SQUARE_SIZE * 5 ) + 1, selectorOffset.y + ( PIECE_SQUARE_SIZE * 5 ), DARKGRAY );
    DrawLine(selectorOffset.x, selectorOffset.y + ( PIECE_SQUARE_SIZE * 5 ), selectorOffset.x + ( PIECE_SQUARE_SIZE * 5 ), selectorOffset.y + ( PIECE_SQUARE_SIZE * 5 ) + 1, DARKGRAY );
}

// Draw game (one frame)
void GameScreen::DrawGame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!gameOver)
    {
        DrawBoard::Draw(gb);
        DrawPiecesOnBoard::Draw(gb);

        DrawGamePieces();

        if( selected )
        {
            DrawPiecesOnBoard::Draw(overlayBoard);
        }

        std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
        std::shared_ptr<Player> player;
        mPlayerManager.GetPlayer(uuid, player);

        if( currentPlayersTurn == player->getPlayerId() )
        {
            DrawSelector();
        }
        else
        {
            DrawText("WAITING FOR NEXT TURN", screenWidth/2 - MeasureText("WAITING FOR NEXT TURN", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
        
        if (pause)
        {
            DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
    }
    else
    {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
    }

    EndDrawing();
}

void GameScreen::CheckForNotification()
{
    if( mReadGameNotification.CheckEvent() )
    {
        GameNotification gn;
        if( mReadGameNotification.Receive(gn) )
        {
            std::stringstream ss;
            ss << gn;
            spdlog::get("console")->trace("GameLobbyScreen::UpdateGameLobbyDrawFrame() - Received notification [ {} ]", ss.str());

            switch(gn.getType())
            {
                case NotificationType::JOIN:
                {
                    // nothing prevents someone from joining the network built with zyre
                    //
                    // that is why the game requires a user register to enforce players actually
                    // participating in the game
                    break;
                }
                
                case NotificationType::MESSAGE:
                {
                    mMessageProcessor.ProcessMessage(gn.getData());
                    break;
                }
                case NotificationType::LEAVE:
                {
                    // if a remote player closes the app
                    // the other players on the network might only get the EXIT message
                    mPlayerManager.RemovePlayerFromGame(gn.getUuid());
                    break;
                }
                default:
                {
                    spdlog::get("console")->warn("GameLobbyScreen::UpdateGameLobbyDrawFrame() - Unknown notification [ {} ]");
                    break;
                }
            }
        }
        else
        {
            spdlog::get("stderr")->warn("GameLobbyScreen::UpdateGameLobbyDrawFrame() - Unknown notification [ {} ]");
        }
    }
}

// Update and Draw (one frame)
void GameScreen::UpdateDrawFrame(void)
{
    CheckForNotification();
    UpdateGame();
    DrawGame();
}

// Unload game variables
void GameScreen::UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

bool GameScreen::Show()
{
    InitGame();
    
    std::stringstream sstream;
    sstream << "Blokus";
    sstream << " - ";
    std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
    sstream << uuid;
    sstream << " - ";
    std::shared_ptr<Player> player;
    mPlayerManager.GetPlayer(uuid, player);
    sstream << PlayerIdString::PrintPlayerIdString(player->getPlayerId());
    
    InitWindow(screenWidth, screenHeight, sstream.str().c_str());

    SetTargetFPS(30);

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    UnloadGame();

    return false;
}

