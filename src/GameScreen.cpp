extern "C" {
#include "raylib.h"
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <vector>
#include <iostream>

#include "ValidateMove.hpp"

#include "GridSquare.hpp"
#include "CalculatePadding.hpp"
#include "Point.hpp"
#include "Layout.hpp"

#include "Piece.hpp"
#include "AddPiece.hpp"
#include "ClearBoard.hpp"

#include "CheckBoundaries.hpp"

#include "GameBoard.hpp"
#include "OverlayBoard.hpp"

#include "GameScreen.hpp"

#define MAX_INPUT_CHARS     9

#define BOARD_SQUARE_SIZE       20
#define PIECE_SQUARE_SIZE       10

#define GRID_HORIZONTAL_SIZE    20
#define GRID_VERTICAL_SIZE      20

static const int screenWidth = 600;
static const int screenHeight = 600;

static bool started = false;
static bool gameOver = false;
static bool pause = false;

GameBoard GameBoard;
OverlayBoard OverlayBoard;

std::vector<Piece> GamePieces;

static bool selected = false;
static unsigned int PieceSelector = 0;
static Piece SelectedPiece; // init

static int PiecePositionX = 0;
static int PiecePositionY = 0;

static Color playerColor;

static bool beginPlay = true;

static int lines = 0;

GameScreen::GameScreen()
{
    
}

GameScreen::~GameScreen()
{

}

void GameScreen::InitializeGamePieces()
{
    // 25 + (( PIECE_SQUARE_SIZE * 5 ) + 50) * i
    Layout BlokusPiece1;
    BlokusPiece1.Set( Point(2, 2), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 25, 25 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece1), BlokusPiece1 ) );

    Layout BlokusPiece2;
    BlokusPiece2.Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(2, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 125, 25 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece2), BlokusPiece2 ) );

    Layout BlokusPiece3;
    BlokusPiece3.Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(2, 3), GridSquare::P1 )
                .Set( Point(3, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 225, 25 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece3), BlokusPiece3 ) );

    Layout BlokusPiece4;
    BlokusPiece4.Set( Point(2, 1), GridSquare::P1 )
                .Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(2, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 325, 25 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece4), BlokusPiece4 ) );

    Layout BlokusPiece5;
    BlokusPiece5.Set( Point(2, 1), GridSquare::P1 )
                .Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(3, 1), GridSquare::P1 )
                .Set( Point(3, 2), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 425, 25 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece5), BlokusPiece5 ) );

    // 25 + (( PIECE_SQUARE_SIZE * 5 ) + 50) * ( i - 5 )
    Layout BlokusPiece6;
    BlokusPiece6.Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(3, 1), GridSquare::P1 )
                .Set( Point(3, 2), GridSquare::P1 )
                .Set( Point(3, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 525, 25 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece6), BlokusPiece6 ) );

    Layout BlokusPiece7;
    BlokusPiece7.Set( Point(2, 1), GridSquare::P1 )
                .Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(2, 3), GridSquare::P1 )
                .Set( Point(2, 4), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 525, 125 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece7), BlokusPiece7 ) );

    Layout BlokusPiece8;
    BlokusPiece8.Set( Point(1, 3), GridSquare::P1 )
                .Set( Point(2, 1), GridSquare::P1 )
                .Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(2, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 525, 225 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece8), BlokusPiece8 ) );

    Layout BlokusPiece9;
    BlokusPiece9.Set( Point(2, 2), GridSquare::P1 )
                .Set( Point(2, 3), GridSquare::P1 )
                .Set( Point(3, 1), GridSquare::P1 )
                .Set( Point(3, 2), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 525, 325 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece9), BlokusPiece9 ) );

    Layout BlokusPiece10;
    BlokusPiece10.Set( Point(2, 4), GridSquare::P1 )
                 .Set( Point(3, 1), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 )
                 .Set( Point(3, 3), GridSquare::P1 )
                 .Set( Point(3, 4), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 525, 425 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece10), BlokusPiece10 ) );

    // 25 + (( PIECE_SQUARE_SIZE * 5 ) + 50) * ( i - 9 );
    Layout BlokusPiece11;
    BlokusPiece11.Set( Point(1, 2), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(3, 1), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 )
                 .Set( Point(3, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 525, 525 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece11), BlokusPiece11 ) );

    Layout BlokusPiece12;
    BlokusPiece12.Set( Point(1, 1), GridSquare::P1 )
                 .Set( Point(2, 1), GridSquare::P1 )
                 .Set( Point(3, 1), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 )
                 .Set( Point(3, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 425, 525 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece12), BlokusPiece12 ) );

    Layout BlokusPiece13;
    BlokusPiece13.Set( Point(3, 1), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(2, 3), GridSquare::P1 )
                 .Set( Point(2, 4), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 325, 525 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece13), BlokusPiece13 ) );

    Layout BlokusPiece14;
    BlokusPiece14.Set( Point(1, 3), GridSquare::P1 )
                 .Set( Point(2, 1), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(2, 3), GridSquare::P1 )
                 .Set( Point(3, 1), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 225, 525 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece14), BlokusPiece14 ) );

    Layout BlokusPiece15;
    BlokusPiece15.Set( Point(2, 0), GridSquare::P1 )
                 .Set( Point(2, 1), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(2, 3), GridSquare::P1 )
                 .Set( Point(2, 4), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 125, 525 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece15), BlokusPiece15 ) );

    // 25 + (( PIECE_SQUARE_SIZE * 5 ) + 50) * ( i - 14 );
    Layout BlokusPiece16;
    BlokusPiece16.Set( Point(1, 1), GridSquare::P1 )
                 .Set( Point(2, 1), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(3, 1), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 25, 525 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece16), BlokusPiece16 ) );

    Layout BlokusPiece17;
    BlokusPiece17.Set( Point(1, 3), GridSquare::P1 )
                 .Set( Point(1, 2), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(2, 1), GridSquare::P1 )
                 .Set( Point(3, 1), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 25, 425 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece17), BlokusPiece17 ) );

    Layout BlokusPiece18;
    BlokusPiece18.Set( Point(1, 2), GridSquare::P1 )
                 .Set( Point(1, 3), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 )
                 .Set( Point(3, 3), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 25, 325 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece18), BlokusPiece18 ) );

    Layout BlokusPiece19;
    BlokusPiece19.Set( Point(1, 2), GridSquare::P1 )
                 .Set( Point(1, 3), GridSquare::P1 )
                 .Set( Point(2, 1), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 25, 225 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece19), BlokusPiece19 ) );

    Layout BlokusPiece20;
    BlokusPiece20.Set( Point(1, 2), GridSquare::P1 )
                 .Set( Point(2, 1), GridSquare::P1 )
                 .Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(2, 3), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 25, 125 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece20), BlokusPiece20 ) );

    Layout BlokusPiece21;
    BlokusPiece21.Set( Point(2, 2), GridSquare::P1 )
                 .Set( Point(3, 1), GridSquare::P1 )
                 .Set( Point(3, 2), GridSquare::P1 )
                 .Set( Point(3, 3), GridSquare::P1 )
                 .Set( Point(3, 4), GridSquare::P1 );
    GamePieces.push_back( Piece( Point( 25, 25 ), CalculatePadding::CalculatePaddingFromLayout(BlokusPiece21), BlokusPiece21 ) );
}

// Initialize game variables
void GameScreen::InitGame(void)
{
    // Initialize game statistics
    lines = 0;

    playerColor = RED;

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
                GameBoard.Set( Point(i, j), GridSquare::BLOCK );
            }
            else
            {
                GameBoard.Set( Point(i, j), GridSquare::EMPTY );
            }
        }
    }

    for (int i = 0; i < GRID_HORIZONTAL_SIZE; i++)
    {
        for (int j = 0; j < GRID_VERTICAL_SIZE; j++)
        {
            if ((j == GRID_VERTICAL_SIZE - 1) || (i == 0) || (i == GRID_HORIZONTAL_SIZE - 1) || (j == 0))
            {
                OverlayBoard.Set( Point(i, j), GridSquare::BLOCK );
            }
            else
            {
                OverlayBoard.Set( Point(i, j), GridSquare::EMPTY );
            }
        }
    }

    InitializeGamePieces();
}

bool GameScreen::ProcessPlayerMove()
{
    Point PlayerMoveLocation( PiecePositionX, PiecePositionY );
    if ( ValidateMove::ValidatePlayerMove( GameBoard, SelectedPiece, PlayerMoveLocation ) )
    {
        AddPiece::AddPieceToBoard( GameBoard, SelectedPiece, PlayerMoveLocation );
        return true;
    }
    else
    {
        return false;
    }
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

        if (!pause)
        {
            if( selected )
            {
                if ( IsKeyPressed(KEY_ESCAPE) )
                {
                    selected = false;
                }

                if ( IsKeyPressed(KEY_LEFT) )
                {
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), SelectedPiece, MovementDirection::LEFT ) )
                    {
                        ClearBoard::EmptyBoard( OverlayBoard );

                        PiecePositionY--;

                        AddPiece::AddPieceToBoard( OverlayBoard, SelectedPiece, Point( PiecePositionX, PiecePositionY ) );
                    }
                }

                if ( IsKeyPressed(KEY_RIGHT) )
                {
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), SelectedPiece, MovementDirection::RIGHT ) )
                    {
                        ClearBoard::EmptyBoard( OverlayBoard );

                        PiecePositionY++;

                        AddPiece::AddPieceToBoard( OverlayBoard, SelectedPiece, Point( PiecePositionX, PiecePositionY ) );
                    }
                }

                if ( IsKeyPressed(KEY_UP) )
                {
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), SelectedPiece, MovementDirection::UP ) )
                    {
                        ClearBoard::EmptyBoard( OverlayBoard );

                        PiecePositionX--;

                        AddPiece::AddPieceToBoard( OverlayBoard, SelectedPiece, Point( PiecePositionX, PiecePositionY ) );
                    }
                }

                if ( IsKeyPressed(KEY_DOWN) )
                {
                    if ( CheckBoundaries::CheckGameBoardBoundary( Point( PiecePositionX, PiecePositionY ), SelectedPiece, MovementDirection::DOWN ) )
                    {
                        ClearBoard::EmptyBoard( OverlayBoard );

                        PiecePositionX++;

                        AddPiece::AddPieceToBoard( OverlayBoard, SelectedPiece, Point( PiecePositionX, PiecePositionY ) );
                    }
                }

                if ( IsKeyPressed(KEY_ENTER) )
                {
                    if ( ProcessPlayerMove() )
                    {
                        selected = false;
                    }
                }
            }
            else
            {
                if ( IsKeyPressed(KEY_SPACE) )
                {
                    // move the selector
                    if ( PieceSelector >= GamePieces.size() - 1 )
                    {
                        PieceSelector = 0;
                    }
                    else
                    {
                        PieceSelector++;
                    }
                }

                if ( IsKeyPressed(KEY_ENTER) )
                {
                    PiecePositionX = 8;
                    PiecePositionY = 8;

                    SelectedPiece.SetOffset( Point( screenWidth / 2 - BOARD_SQUARE_SIZE * 2, screenHeight / 2 - BOARD_SQUARE_SIZE * 2 ) );
                    std::cout << SelectedPiece.GetOffset() << std::endl;
                    SelectedPiece.SetPadding(GamePieces.at(PieceSelector).GetPadding());
                    std::cout << SelectedPiece.GetPadding() << std::endl;
                    SelectedPiece.SetLayout(GamePieces.at(PieceSelector).GetLayout());
                    std::cout << SelectedPiece.GetLayout() << std::endl;

                    AddPiece::AddPieceToBoard( OverlayBoard, SelectedPiece, Point( PiecePositionX, PiecePositionY ) );

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
            if (GameBoard.Get( Point(i, j) ) == GridSquare::EMPTY)
            {
                DrawLine(offset.x, offset.y, offset.x + BOARD_SQUARE_SIZE, offset.y, LIGHTGRAY );
                DrawLine(offset.x, offset.y, offset.x, offset.y + BOARD_SQUARE_SIZE, LIGHTGRAY );
                DrawLine(offset.x + BOARD_SQUARE_SIZE, offset.y, offset.x + BOARD_SQUARE_SIZE, offset.y + BOARD_SQUARE_SIZE, LIGHTGRAY );
                DrawLine(offset.x, offset.y + BOARD_SQUARE_SIZE, offset.x + BOARD_SQUARE_SIZE, offset.y + BOARD_SQUARE_SIZE, LIGHTGRAY );
                offset.x += BOARD_SQUARE_SIZE;
            }
            else if (GameBoard.Get( Point(i, j) ) == GridSquare::BLOCK)
            {
                DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, LIGHTGRAY);
                offset.x += BOARD_SQUARE_SIZE;
            }
            else
            {
                DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, playerColor);
                offset.x += BOARD_SQUARE_SIZE;
            }
        }

        offset.x = controller;
        offset.y += BOARD_SQUARE_SIZE;
    }
}

void GameScreen::DrawGamePieces()
{
    // Draw incoming piece (hardcoded)
    for (auto po : GamePieces)
    {
        Vector2 pieceOffset;

        pieceOffset.x = po.GetOffset().GetX();
        pieceOffset.y = po.GetOffset().GetY();

        int controller = pieceOffset.x;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (po.GetLayout().Get(i, j) == GridSquare::EMPTY)
                {
                    DrawLine(pieceOffset.x, pieceOffset.y, pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y, LIGHTGRAY );
                    DrawLine(pieceOffset.x, pieceOffset.y, pieceOffset.x, pieceOffset.y + PIECE_SQUARE_SIZE, LIGHTGRAY );
                    DrawLine(pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y, pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y + PIECE_SQUARE_SIZE, LIGHTGRAY );
                    DrawLine(pieceOffset.x, pieceOffset.y + PIECE_SQUARE_SIZE, pieceOffset.x + PIECE_SQUARE_SIZE, pieceOffset.y + PIECE_SQUARE_SIZE, LIGHTGRAY );
                    pieceOffset.x += PIECE_SQUARE_SIZE;
                }
                else if (po.GetLayout().Get(i, j) == GridSquare::BLOCK)
                {
                    // won't happen
                    pieceOffset.x += BOARD_SQUARE_SIZE;
                }
                else
                {
                    DrawRectangle(pieceOffset.x, pieceOffset.y, PIECE_SQUARE_SIZE, PIECE_SQUARE_SIZE, playerColor);
                    pieceOffset.x += PIECE_SQUARE_SIZE;
                }
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
                // Draw each square of the grid
                if (OverlayBoard.Get( Point(i, j) ) == GridSquare::EMPTY)
                {
                    // dont draw
                    offset.x += BOARD_SQUARE_SIZE;
                }
                else if (OverlayBoard.Get( Point(i, j) ) == GridSquare::BLOCK)
                {
                    // dont draw
                    offset.x += BOARD_SQUARE_SIZE;
                }
                else
                {
                    DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, playerColor);
                    offset.x += BOARD_SQUARE_SIZE;
                }
            }

            offset.x = controller;
            offset.y += BOARD_SQUARE_SIZE;
        }
    }
}

void GameScreen::DrawSelector()
{
    Vector2 selectorOffset;

    selectorOffset.x = GamePieces.at(PieceSelector).GetOffset().GetX();
    selectorOffset.y = GamePieces.at(PieceSelector).GetOffset().GetY();

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

        DrawSelector();
        
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

// Update and Draw (one frame)
void GameScreen::UpdateDrawFrame(void)
{
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

    SetTargetFPS(30);

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    UnloadGame();

    return false;
}

