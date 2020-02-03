#define BOARD_SQUARE_SIZE       20
#define PIECE_SQUARE_SIZE       10

#define GRID_HORIZONTAL_SIZE    20
#define GRID_VERTICAL_SIZE      20

#include "Validate.hpp"
#include "GridSquare.hpp"
#include "Point.hpp"
#include "Layout.hpp"
#include "Piece.hpp"
#include "PieceTypeString.hpp"
#include "AddPiece.hpp"
#include "ClearBoard.hpp"
#include "MergeBoards.hpp"
#include "GameBoard.hpp"
#include "OverlayBoard.hpp"
#include "GameScreen.hpp"
#include "PlayerMoveRequestData.hpp"
#include "PiecesAvailableForPlayLocations.hpp"
#include "PlayerIdString.hpp"
#include "ManipulatePiece.hpp"
#include "CalculatePieceScore.hpp"
#include "DrawBoard.hpp"
#include "DrawPiecesOnBoard.hpp"

// =============================================================
// NOTE
//
// Important where this include happens
// It can mess with the PlayerColor enum class
// =============================================================
extern "C" {
#include "raylib.h"
}

namespace
{
    static const int screenWidth = 800;
    static const int screenHeight = 600;

    static bool gameOver = false;
    static bool pause = false;

    GameBoard gb;
    OverlayBoard overlayBoard;

    static bool selected = false;
}

#ifdef BLUE
    #undef BLUE
#endif

#ifdef RED
    #undef RED
#endif

#ifdef GREEN
    #undef GREEN
#endif

#ifdef YELLOW
    #undef YELLOW
#endif

#include "PlayerColor.hpp"

extern "C" {
#include "raygui.h"
}

GameScreen::GameScreen(IGameSettings& settings,
                       MessageProcessor& messageProcessor,
                       ReadGameNotification& readGameNotification,
                       PlayerManager& playerManager,
                       ProcessPlayerMove& processPlayerMove,
                       PlayerTurnManager& playerTurnManager,
                       InitialMoveIndicator& initialMoveIndicator,
                       PlayerScores& playerScores   )
:   mSettings(settings),
    mMessageProcessor(messageProcessor),
    mReadGameNotification(readGameNotification),
    mPlayerManager(playerManager),
    mProcessPlayerMove(processPlayerMove),
    mPlayerTurnManager(playerTurnManager),
    mInitialMoveIndicator(initialMoveIndicator),
    mPlayerScores(playerScores),
    mGamePieceBank(),
    mPieceSelector(),
    mSelectedPieceType(mPieceSelector.GetNextPiece()),
    //mSelectedPiece(nullptr)
    mPlayerSelectedPiece(nullptr),
    mCurrentPlayersTurn(std::pair<PlayerId, PlayerColor>(PlayerId::PLAYER_ONE, PlayerColor::BLUE))
{
    spdlog::get("console")->info("GameScreen::GameScreen() - Start");

    // mSelectedPiece = mGamePieceBank.GetPlayerPiece(player->getPlayerId(), mSelectedPieceType);
    mPlayerSelectedPiece = PlayerSelectedPiece(mGamePieceBank.GetPlayerPiece(mCurrentPlayersTurn.second, mSelectedPieceType));
}

GameScreen::~GameScreen()
{
    spdlog::get("console")->info("GameScreen::~GameScreen() - Start");
}

// Initialize game variables
void GameScreen::InitGame(void)
{
    pause = false;

    ClearBoard::EmptyBoard( gb );
    ClearBoard::EmptyBoard( overlayBoard );
}

bool GameScreen::ProcessPlayerMoveInternal()
{
    spdlog::get("console")->info("GameScreen::ProcessPlayerMoveInternal() - Start");

    if ( mInitialMoveIndicator.Check(mCurrentPlayersTurn.second) )
    {
        if ( !Validate::Normal( gb, overlayBoard ) )
        {
            spdlog::get("console")->error("GameScreen::ProcessPlayerMoveInternal() - Invalid location.");
            return false;
        }
    }
    else
    {
        if ( !Validate::InitialMove( gb, overlayBoard ) )
        {
            spdlog::get("console")->error("GameScreen::ProcessPlayerMoveInternal() - Invalid location.");
            return false;
        }

        mInitialMoveIndicator.Perform(mCurrentPlayersTurn.second);
    }

    MergeBoards::Merge(gb, overlayBoard);

    std::string uuid = mPlayerManager.GetLocalPlayerUniqueIdentifier();
    std::shared_ptr<Player> player;
    mPlayerManager.GetPlayer(uuid, player);

    mPlayerScores.AddToScore(player->getPlayerId(), CalculatePieceScore::CalculateFromBoard(overlayBoard));

    PlayerMoveRequestData playerMoveRequestData;
    playerMoveRequestData.SetPlayerId(player->getPlayerId());
    playerMoveRequestData.SetPieceType(mSelectedPieceType);

    overlayBoard.GetPieceData(playerMoveRequestData);

    mProcessPlayerMove.Process(playerMoveRequestData);

    return true;

}

bool GameScreen::ProcessRemotePlayerMove(IPlayerMoveRequestData& data)
{
    spdlog::get("console")->info("GameScreen::ProcessRemotePlayerMove() - Start");

    Piece temporaryPiece = *mGamePieceBank.GetPlayerPiece(mCurrentPlayersTurn.second, data.GetPieceType());
    Layout temporaryLayout = temporaryPiece.GetLayout();

    if (data.GetPieceFlipped())
    {
        ManipulatePiece::Flip(temporaryLayout);
    }

    switch(data.GetPieceRotation())
    {
        case PieceRotation::ZERO_DEGREES:
        {
            break;
        }
        case PieceRotation::NINETY_DEGREES:
        {
            ManipulatePiece::Rotate(temporaryLayout);
            break;
        }
        case PieceRotation::ONE_HUNDRED_EIGHTY_DEGREES:
        {
            ManipulatePiece::Rotate(temporaryLayout);
            ManipulatePiece::Rotate(temporaryLayout);
            break;
        }
        case PieceRotation::TWO_HUNDRED_SEVENTY_DEGREES:
        {
            ManipulatePiece::Rotate(temporaryLayout);
            ManipulatePiece::Rotate(temporaryLayout);
            ManipulatePiece::Rotate(temporaryLayout);
            break;
        }
        default:
        {
            break;
        }
    }
    
    temporaryPiece = Piece(temporaryLayout);
    AddPiece::AddPieceToBoard( gb, temporaryPiece, data.GetLocation() );

    mPlayerScores.AddToScore(data.GetPlayerId(), CalculatePieceScore::CalculateFromLayout(temporaryLayout));

    // advance to next player
    mCurrentPlayersTurn = mPlayerTurnManager.NextPlayersTurn();

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

        if (!pause && ( mCurrentPlayersTurn.first == player->getPlayerId() ))
        {
            if( selected )
            {
                if ( IsKeyPressed(KEY_ENTER) )
                {
                    if ( ProcessPlayerMoveInternal() )
                    {
                        // piece has been played, make piece unavailable to be played again
                        mPlayerSelectedPiece.GetPiece()->PiecePlayed();

                        // advance to next player
                        mCurrentPlayersTurn = mPlayerTurnManager.NextPlayersTurn();

                        selected = false;
                    }
                }
                else
                {
                    if ( IsKeyPressed(KEY_ESCAPE) )
                    {
                        selected = false;
                    }

                    if ( IsKeyPressed(KEY_LEFT) )
                    {
                        overlayBoard.MovePiece(MovementDirection::LEFT);
                    }

                    if ( IsKeyPressed(KEY_RIGHT) )
                    {
                        overlayBoard.MovePiece(MovementDirection::RIGHT);
                    }

                    if ( IsKeyPressed(KEY_UP) )
                    {
                        overlayBoard.MovePiece(MovementDirection::UP);
                    }

                    if ( IsKeyPressed(KEY_DOWN) )
                    {
                        overlayBoard.MovePiece(MovementDirection::DOWN);
                    }

                    if ( IsKeyPressed(KEY_F) )
                    {
                        overlayBoard.FlipPiece();
                    }

                    if ( IsKeyPressed(KEY_R) )
                    {
                        overlayBoard.RotatePiece();
                    }

                    if ( mInitialMoveIndicator.Check( mCurrentPlayersTurn.second ) )
                    {
                        if ( !Validate::Normal( gb, overlayBoard ) )
                        {

                        }
                    }
                    else
                    {
                        if ( !Validate::InitialMove( gb, overlayBoard ) )
                        {

                        }
                    }
                }
            }
            else
            {
                if ( IsKeyPressed(KEY_SPACE) )
                {
                    do
                    {
                        mSelectedPieceType = mPieceSelector.GetNextPiece();
                    }
                    while( mGamePieceBank.GetPlayerPiece(mCurrentPlayersTurn.second, mSelectedPieceType)->HasPieceBeenPlayed() );

                    spdlog::get("console")->info("GameScreen::UpdateGame() - {} Piece Selected", PieceTypeString::PrintPieceTypeString(mSelectedPieceType));
                }

                if ( IsKeyPressed(KEY_ENTER) )
                {
                    mPlayerSelectedPiece = PlayerSelectedPiece(mGamePieceBank.GetPlayerPiece(mCurrentPlayersTurn.second, mSelectedPieceType));
                    
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

        PlayerSelectedPiece piece(mGamePieceBank.GetPlayerPiece(mCurrentPlayersTurn.second, it->first));

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
                    case GridSquare::INVALID:
                    {
                        break;
                    }
                    case GridSquare::PLAYER_ONE:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, (Color){ 0, 121, 241, 255 });
                        break;
                    }
                    case GridSquare::PLAYER_TWO:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, (Color){ 230, 41, 55, 255 });
                        break;
                    }
                    case GridSquare::PLAYER_THREE:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, (Color){ 253, 249, 0, 255 });
                        break;
                    }
                    case GridSquare::PLAYER_FOUR:
                    {
                        DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, (Color){ 0, 228, 48, 255 });
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

void GameScreen::DrawScores()
{
    GuiLabel((Rectangle){620, 20, 50, 20}, "Scores");

    switch(mSettings.GetGameConfiguration())
    {
        case GameConfiguration::TWO_PLAYER:
        {
            GuiLabel((Rectangle){620, 50, 40, 20}, "Player1 : ");
            GuiLabel((Rectangle){660, 50, 50, 20}, std::to_string(mPlayerScores.GetScore(PlayerId::PLAYER_ONE)).c_str());

            GuiLabel((Rectangle){620, 70, 40, 20}, "Player2 : ");
            GuiLabel((Rectangle){660, 70, 50, 20}, std::to_string(mPlayerScores.GetScore(PlayerId::PLAYER_TWO)).c_str());

            break;
        }
        case GameConfiguration::FOUR_PLAYER:
        {
            GuiLabel((Rectangle){620, 50, 40, 20}, "Player1 : ");
            GuiLabel((Rectangle){660, 50, 50, 20}, std::to_string(mPlayerScores.GetScore(PlayerId::PLAYER_ONE)).c_str());

            GuiLabel((Rectangle){620, 70, 40, 20}, "Player2 : ");
            GuiLabel((Rectangle){660, 70, 50, 20}, std::to_string(mPlayerScores.GetScore(PlayerId::PLAYER_TWO)).c_str());

            GuiLabel((Rectangle){620, 90, 40, 20}, "Player3 : ");
            GuiLabel((Rectangle){660, 90, 50, 20}, std::to_string(mPlayerScores.GetScore(PlayerId::PLAYER_THREE)).c_str());

            GuiLabel((Rectangle){620, 110, 40, 20}, "Player4 : ");
            GuiLabel((Rectangle){660, 110, 50, 20}, std::to_string(mPlayerScores.GetScore(PlayerId::PLAYER_FOUR)).c_str());
            break;
        }
        default:
        {
            spdlog::get("console")->info("PlayerTurnManager::PlayerTurnManager() - Unhandled Game Configuration.");
            break;
        }
    }
}

// Draw game (one frame)
void GameScreen::DrawGame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangleRec((Rectangle){ 600, 0, 200, 600 }, (Color){ 80, 80, 80, 255});
    DrawRectangleRec((Rectangle){ 610, 10, 180, 180 }, (Color){ 80, 60, 80, 255});
    DrawRectangleRec((Rectangle){ 610, 210, 180, 380 }, (Color){ 80, 60, 80, 255});

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

        if( mCurrentPlayersTurn.first == player->getPlayerId() )
        {
            DrawSelector();
        }
        else
        {
            DrawText("WAITING FOR NEXT TURN", screenWidth/2 - MeasureText("WAITING FOR NEXT TURN", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }

        DrawScores();
        
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

    GuiLoadStyleDefault();

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    UnloadGame();

    return false;
}

