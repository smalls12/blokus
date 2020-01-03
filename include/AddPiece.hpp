#pragma once

#include "Board.hpp"
#include "Piece.hpp"
#include "Point.hpp"

#include "GridSquareString.hpp"

class AddPiece
{
    public:
        // NOTE
        // Might only need layout instead of Piece
        inline static void AddPieceToBoard(Board& board, Piece piece, Point point)
        {
            // y-axis
            for (int i = 0; i < 5; i++)
            {
                // x-axis
                for (int j = 0; j < 5; j++)
                {
                    // std::cout << "(i, j) : (" << i << ", " << j << ") : (" << GridSquareString::PrintGridSquareString(piece.GetLayout().Get(i, j)) << ")" << std::endl; 
                    board.Set( Point(point.GetX() + i, point.GetY() + j), piece.GetLayout().Get(i, j) );
                }
            }
        }
};