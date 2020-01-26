#pragma once

#include "Layout.hpp"

class ManipulatePiece
{
    public:
        inline static void Rotate(Layout& layout)
        {
            Layout originalLayout = layout;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    layout.Set( Point(i, j), originalLayout.Get(4 - j, i) );
                }
            }
        }

        inline static void Flip(Layout& layout)
        {
            Layout originalLayout = layout;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    layout.Set( Point(i, j), originalLayout.Get(4 - i, j) );
                }
            }
        }

        inline static void Mirror(Layout& layout)
        {
            Layout originalLayout = layout;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    layout.Set( Point(i, j), originalLayout.Get(i, 4 - j) );
                }
            }
        }
};