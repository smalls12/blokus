#pragma once

#include "Layout.hpp"
#include "Padding.hpp"

class CalculatePadding
{
    public:
        inline static Padding CalculatePaddingFromLayout(Layout layout)
        {
            // calculate top padding

            int top = 0;
            for (int i = 0; i < 5; i++)
            {
                int row = 0;
                for (int j = 0; j < 5; j++)
                {
                    if ( layout.Get(i, j) == GridSquare::EMPTY )
                    {
                        row++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (row == 5)
                {
                    // row is clear
                    top++;
                }
                else
                {
                    break;
                }
            }

            // calculate bottom padding

            int bottom = 0;
            for (int i = 0; i < 5; i++)
            {
                int row = 0;
                for (int j = 0; j < 5; j++)
                {
                    if ( layout.Get(4 - i, j) == GridSquare::EMPTY )
                    {
                        row++;
                    }
                    else
                    {
                        break;
                    }
                }
                
                if (row == 5)
                {
                    // row is clear
                    bottom++;
                }
                else
                {
                    break;
                }
            }

            // calculate left padding

            int left = 0;
            for (int i = 0; i < 5; i++)
            {
                int column = 0;
                for (int j = 0; j < 5; j++)
                {
                    if ( layout.Get(j, i) == GridSquare::EMPTY )
                    {
                        column++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (column == 5)
                {
                    left++;
                }
                else
                {
                    break;
                }
                
            }

            // calculate right padding

            int right = 0;
            for (int i = 0; i < 5; i++)
            {
                int column = 0;
                for (int j = 0; j < 5; j++)
                {
                    if ( layout.Get(j, 4 - i) == GridSquare::EMPTY )
                    {
                        column++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (column == 5)
                {
                    right++;
                }
                else
                {
                    break;
                }
                
            }

            return Padding(left, top, right, bottom);
        }
};