#pragma once

#include "GridSquare.hpp"
#include "Point.hpp"

class Board
{
    public:
        GridSquare Get(Point point);
        Board& Set(Point point, GridSquare value);

    private:
        GridSquare mGrid [20][20];
};