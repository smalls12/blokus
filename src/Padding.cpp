#include "Padding.hpp"

Padding::Padding()
:   mLeft(0),
    mTop(0),
    mRight(0),
    mBottom(0)
{

}

Padding::Padding(int left, int top, int right, int bottom)
:   mLeft(left),
    mTop(top),
    mRight(right),
    mBottom(bottom)
{

}

int Padding::GetLeft()
{
    return mLeft;
}

int Padding::GetTop()
{
    return mTop;
}

int Padding::GetRight()
{
    return mRight;
}

int Padding::GetBottom()
{
    return mBottom;
}

std::ostream& operator <<(std::ostream& outputStream, const Padding& p)
{
    outputStream << "Left=" << p.mLeft << "," << "Top=" << p.mTop << "," << "Right=" << p.mRight << "," << "Bottom=" << p.mBottom;
    return outputStream;
}