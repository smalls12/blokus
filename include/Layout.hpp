#pragma once

#include "GridSquare.hpp"
#include "Point.hpp"

class Layout
{
    public:
        Layout();

        GridSquare Get(int x, int y);
        Layout& Set(Point point, GridSquare value);

        friend bool operator==(const Layout &l, const Layout &r)
        {
            // check for same object being compared
            if(&l == &r)
            {
                return true;
            }
            
            // check grid comparison
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if( l.mGrid[i][j] != r.mGrid[i][j] )
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        friend std::ostream& operator <<(std::ostream& outputStream, const Layout& p);
    
    private:
        GridSquare mGrid [5][5];
};