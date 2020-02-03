#pragma once

#include "Board.hpp"

extern "C" {
#include "raylib.h"
}

class DrawBoard
{
    public:
        inline static void Draw(Board& board)
        {
            // Draw gameplay area
            Vector2 offset;
            
            offset.x = 100;
            offset.y = 100;

            int controller = offset.x;

            for (int i = 0; i < GRID_VERTICAL_SIZE; i++)
            {
                for (int j = 0; j < GRID_HORIZONTAL_SIZE; j++)
                {
                    // Draw each square of the grid
                    switch( board.Get(Point(i, j)) )
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