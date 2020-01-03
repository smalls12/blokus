#include "Layout.hpp"

#include "GridSquareString.hpp"

Layout::Layout()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            mGrid[i][j] = GridSquare::EMPTY;
        }
    }
}

GridSquare Layout::Get(int x, int y)
{
    return mGrid[x][y];
}

Layout& Layout::Set(Point point, GridSquare value)
{
    mGrid[point.GetX()][point.GetY()] = value;
    return *this;
}

std::ostream& operator <<(std::ostream& outputStream, const Layout& l)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            outputStream << GridSquareString::PrintGridSquareString(l.mGrid[i][j]) << "\t";
        }
        outputStream << "\n";
    }
    return outputStream;
}