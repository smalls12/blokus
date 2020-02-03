#pragma once

#include "Layout.hpp"
#include "Board.hpp"

class CalculatePieceScore
{
    public:

        inline static unsigned int CalculateFromLayout(Layout& layout)
        {
            unsigned int score = 0;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if ( layout.Get(i, j) != GridSquare::EMPTY )
                    {
                        score++;
                    }
                }
            }

            return score;
        }

        inline static unsigned int CalculateFromBoard(Board& board)
        {
            unsigned int score = 0;
            for (int i = 1; i < 19; i++)
            {
                for (int j = 1; j < 19; j++)
                {
                    if ( board.Get( Point(i, j) ) != GridSquare::EMPTY )
                    {
                        score++;
                    }
                }
            }

            return score;
        }
};