#pragma once

#include "GridSquare.hpp"
#include "Point.hpp"

class Layout
{
    public:
        Layout();

        GridSquare Get(int x, int y);
        Layout& Set(Point point, GridSquare value);

        friend std::ostream& operator <<(std::ostream& outputStream, const Layout& p);
    
    private:
        GridSquare mGrid [5][5];
};