#pragma once

#include <ostream>

class Point
{
    public:
        Point();
        Point(int x, int y);

        int GetX() const;
        int GetY() const;

        friend std::ostream& operator <<(std::ostream& outputStream, const Point& p);

    private:
        int mX;
        int mY;   
};