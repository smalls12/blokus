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

        friend std::ostream& operator <<(std::ostream& outputStream, const Padding& p);

    private:
        int mLeft;
        int mTop;
        int mRight;
        int mBottom;   
};