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

int Point::GetX()
{
    return mX;
}

int Point::GetY()
{
    return mY;
}

std::ostream& operator <<(std::ostream& outputStream, const Point& p)
{
    outputStream << "x=" << p.mX << "," << "y=" << p.mY;
    return outputStream;
}