#pragma once

#include "Board.hpp"
#include "Point.hpp"

class MergeBoards
{
    public:
        // take the pieces from the overlay and add to the base
        inline static bool Merge(Board& base, Board& overlay)
        {
            for (int i = 1; i < 19; i++)
            {
                for (int j = 1; j < 19; j++)
                {
                    base.Set( Point(i, j), overlay.Get( Point(i, j) ) );
                }
            }

            return true;
        }
};