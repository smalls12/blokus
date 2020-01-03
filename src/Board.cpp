#include "Board.hpp"

GridSquare Board::Get(Point point)
{
    return mGrid[point.GetX()][point.GetY()];
}

Board& Board::Set(Point point, GridSquare value)
{
    mGrid[point.GetX()][point.GetY()] = value;
    return *this;
}