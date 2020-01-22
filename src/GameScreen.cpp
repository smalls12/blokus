#include "ValidateMove.hpp"

#include "GridSquare.hpp"
#include "Point.hpp"
#include "Layout.hpp"

#include "Piece.hpp"
#include "PieceTypeString.hpp"

#include "AddPiece.hpp"
#include "ClearBoard.hpp"

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

#define BOARD_SQUARE_SIZE       20
#define PIECE_SQUARE_SIZE       10

#define GRID_HORIZONTAL_SIZE    20
#define GRID_VERTICAL_SIZE      20

namespace
{
    static const int screenWidth = 600;
    static const int screenHeight = 600;

    static bool gameOver = false;
    static bool pause = false;

    GameBoard gb;
    OverlayBoard ob;

    static bool selected = false;

    static int PiecePositionX = 0;
    static int PiecePositionY = 0;

    static bool beginPlay = true;

    static PlayerId currentPlayersTurn = PlayerId::PLAYER_ONE;
}

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
    PiecePositionX = 0;
    PiecePositionY = 0;

    pause = false;

    beginPlay = true;

    // Initialize grid matrices
    for (int i = 0; i < GRID_HORIZONTAL_SIZE; i++)
    {
        for (int j = 0; j < GRID_VERTICAL_SIZE; j++)
        {
            if ((j == GRID_VERTICAL_SIZE - 1) || (i == 0) || (i == GRID_HORIZONTAL_SIZE - 1) || (j == 0))
            {
                gb.Set( Point(i, j), GridSquare::BLOCK );
            }
            else
            {
                gb.Set( Point(i, j), GridSquare::EMPTY );
            }
        }
    }

    for (int i = 0; i < GRID_HORIZONTAL_SIZE; i++)
    {
        for (int j = 0; j < GRID_VERTICAL_SIZE; j++)
        {
            if ((j == GRID_VERTICAL_SIZE - 1) || (i == 0) || (i == GRID_HORIZONTAL_SIZE - 1) || (j == 0))
            {
                ob.Set( Point(i, j), GridSquare::BLOCK );
            }
            else
            {
                ob.Set( Point(i, j), GridSquare::EMPTY );
            }
        }
    }
}

bool GameScreen::ProcessPlayerMoveInternal()
{
    spdlog::get("console")->info("GameScreen::ProcessPlayerMoveInternal() - Start");

    Point PlayerMoveLocation( PiecePositionX, PiecePositionY );
    if ( ValidateMove::ValidatePlayerMove( gb, *mPlayerSelectedPiece.GetPiece(), PlayerMoveLocation ) )
    {
        AddPiece::AddPieceToBoard( gb, *mPlayerSelectedPiece.GetPiece(), PlayerMoveLocation );

        std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
        std::shared_ptr<Player> player;
        mPlayerManager.GetPlayer(uuid, player);

        PlayerMoveRequestData playerMoveRequestData;
        playerMoveRequestData.SetPlayerId(player->getPlayerId());
        playerMoveRequestData.SetPieceType(mSelectedPieceType);
        playerMoveRequestData.SetLocation(PlayerMoveLocation);

        mProcessPlayerMove.Process(playerMoveRequestData);

        return true;
    }
    else
    {
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
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), *mPlayerSelectedPiece.GetPiece(), MovementDirection::LEFT ) )
                    {
                        ClearBoard::EmptyBoard( ob );

                        PiecePositionY--;

                        AddPiece::AddPieceToBoard( ob, *mPlayerSelectedPiece.GetPiece(), Point( PiecePositionX, PiecePositionY ) );
                    }
                }

                if ( IsKeyPressed(KEY_RIGHT) )
                {
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), *mPlayerSelectedPiece.GetPiece(), MovementDirection::RIGHT ) )
                    {
                        ClearBoard::EmptyBoard( ob );

                        PiecePositionY++;

                        AddPiece::AddPieceToBoard( ob, *mPlayerSelectedPiece.GetPiece(), Point( PiecePositionX, PiecePositionY ) );
                    }
                }

                if ( IsKeyPressed(KEY_UP) )
                {
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), *mPlayerSelectedPiece.GetPiece(), MovementDirection::UP ) )
                    {
                        ClearBoard::EmptyBoard( ob );

                        PiecePositionX--;

                        AddPiece::AddPieceToBoard( ob, *mPlayerSelectedPiece.GetPiece(), Point( PiecePositionX, PiecePositionY ) );
                    }
                }

                if ( IsKeyPressed(KEY_DOWN) )
                {
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), *mPlayerSelectedPiece.GetPiece(), MovementDirection::DOWN ) )
                    {
                        ClearBoard::EmptyBoard( ob );

                        PiecePositionX++;

                        AddPiece::AddPieceToBoard( ob, *mPlayerSelectedPiece.GetPiece(), Point( PiecePositionX, PiecePositionY ) );
                    }
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
                    PiecePositionX = 8;
                    PiecePositionY = 8;

                    std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
                    std::shared_ptr<Player> player;
                    mPlayerManager.GetPlayer(uuid, player);

                    mPlayerSelectedPiece = PlayerSelectedPiece(mGamePieceBank.GetPlayerPiece(player->getPlayerId(), mSelectedPieceType));
                    mPlayerSelectedPiece.GetPiece()->SetLocation(Point( screenWidth / 2 - BOARD_SQUARE_SIZE * 2, screenHeight / 2 - BOARD_SQUARE_SIZE * 2 ));

                    AddPiece::AddPieceToBoard( ob, *mPlayerSelectedPiece.GetPiece(), Point( PiecePositionX, PiecePositionY ) );

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

void GameScreen::DrawBoard()
{
    // Draw gameplay area
    Vector2 offset;
    
    offset.x = screenWidth / 2 - (( BOARD_SQUARE_SIZE * 20 ) / 2);
    offset.y = screenHeight / 2 - (( BOARD_SQUARE_SIZE * 20 ) / 2);

    int controller = offset.x;

    for (int i = 0; i < GRID_VERTICAL_SIZE; i++)
    {
        for (int j = 0; j < GRID_HORIZONTAL_SIZE; j++)
        {
            // Draw each square of the grid
            switch( gb.Get(Point(i, j)) )
            {
                case GridSquare::EMPTY:
                {
                    DrawLine(offset.x, offset.y, offset.x + BOARD_SQUARE_SIZE, offset.y, LIGHTGRAY );
                    DrawLine(offset.x, offset.y, offset.x, offset.y + BOARD_SQUARE_SIZE, LIGHTGRAY );
                    DrawLine(offset.x + BOARD_SQUARE_SIZE, offset.y, offset.x + BOARD_SQUARE_SIZE, offset.y + BOARD_SQUARE_SIZE, LIGHTGRAY );
                    DrawLine(offset.x, offset.y + BOARD_SQUARE_SIZE, offset.x + BOARD_SQUARE_SIZE, offset.y + BOARD_SQUARE_SIZE, LIGHTGRAY );
                    break;
                }
                case GridSquare::BLOCK:
                {
                    DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, LIGHTGRAY);
                    break;
                }
                case GridSquare::PLAYER_ONE:
                {
                    DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BLUE);
                    break;
                }
                case GridSquare::PLAYER_TWO:
                {
                    DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, RED);
                    break;
                }
                case GridSquare::PLAYER_THREE:
                {
                    DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, YELLOW);
                    break;
                }
                case GridSquare::PLAYER_FOUR:
                {
                    DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, GREEN);
                    break;
                }
                default:
                {
                    break;
                }
            }

            offset.x += BOARD_SQUARE_SIZE;
        }

        offset.x = controller;
        offset.y += BOARD_SQUARE_SIZE;
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

void GameScreen::DrawOverlayBoard()
{
    if (selected)
    {
        // Draw gameplay area
        Vector2 offset;
        
        offset.x = screenWidth / 2 - (( BOARD_SQUARE_SIZE * 20 ) / 2);
        offset.y = screenHeight / 2 - (( BOARD_SQUARE_SIZE * 20 ) / 2);

        int controller = offset.x;

        for (int i = 0; i < GRID_VERTICAL_SIZE; i++)
        {
            for (int j = 0; j < GRID_HORIZONTAL_SIZE; j++)
            {
                switch( ob.Get( Point(i, j) ) )
                {
                    case GridSquare::EMPTY:
                    {
                        break;
                    }
                    case GridSquare::BLOCK:
                    {
                        break;
                    }
                    case GridSquare::PLAYER_ONE:
                    {
                        DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BLUE);
                        break;
                    }
                    case GridSquare::PLAYER_TWO:
                    {
                        DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, RED);
                        break;
                    }
                    case GridSquare::PLAYER_THREE:
                    {
                        DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, YELLOW);
                        break;
                    }
                    case GridSquare::PLAYER_FOUR:
                    {
                        DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, GREEN);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                offset.x += BOARD_SQUARE_SIZE;
            }

            offset.x = controller;
            offset.y += BOARD_SQUARE_SIZE;
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
        DrawBoard();

        DrawGamePieces();

        DrawOverlayBoard();

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

