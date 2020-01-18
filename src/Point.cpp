#include "Point.hpp"

Point::Point()
:   mX(0),
    mY(0)
{

}

Point::Point(int x, int y)
:   mX(x),
    mY(y)
{

}

int Point::GetX() const
{
    return mX;
}

int Point::GetY() const
{
    return mY;
}

std::ostream& operator <<(std::ostream& outputStream, const Point& p)
{
    outputStream << "x=" << p.mX << "," << "y=" << p.mY;
    return outputStream;
}