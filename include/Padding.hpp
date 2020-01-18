#pragma once

#include <ostream>

class Padding
{
    public:
        Padding();
        Padding(int left, int top, int right, int bottom);

        int GetLeft();
        int GetTop();
        int GetRight();
        int GetBottom();

        friend bool operator==(const Padding &l, const Padding &r)
        {
            // check for same object being compared
            if(&l == &r)
            {
                return true;
            }
            
            if( l.mLeft != r.mLeft)
            {
                return false;
            }

            if( l.mTop != r.mTop)
            {
                return false;
            }

            if( l.mRight != r.mRight)
            {
                return false;
            }

            if( l.mBottom != r.mBottom)
            {
                return false;
            }

            return true;
        }

        friend std::ostream& operator <<(std::ostream& outputStream, const Padding& p);

    private:
        int mLeft;
        int mTop;
        int mRight;
        int mBottom;   
};