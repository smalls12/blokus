#pragma once

#include "Board.hpp"

extern "C" {
#include "raylib.h"
}

class DrawPiecesOnBoard
{
    public:
        inline static void Draw(Board& board)
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
                    switch( board.Get( Point(i, j) ) )
                    {
                        case GridSquare::INVALID:
                        {
                            DrawRectangle(offset.x, offset.y, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, DARKGREEN);

                            DrawLine(offset.x, offset.y, offset.x + BOARD_SQUARE_SIZE, offset.y + BOARD_SQUARE_SIZE, BLACK );
                            DrawLine(offset.x + BOARD_SQUARE_SIZE, offset.y, offset.x, offset.y + BOARD_SQUARE_SIZE, BLACK );

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
};