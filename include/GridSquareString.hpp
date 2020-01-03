#pragma once

#include "GridSquare.hpp"

#include <sstream>

class GridSquareString
{
    public:
        inline static std::string PrintGridSquareString(GridSquare gs)
        {
            std::stringstream sstream;
            switch (gs)
            {
                case GridSquare::EMPTY:
                {
                    sstream << "EMPTY";
                    break;
                }
                case GridSquare::BLOCK:
                {
                    sstream << "BLOCK";
                    break;
                }
                case GridSquare::P1:
                {
                    sstream << "P1";
                    break;
                }
                case GridSquare::P2:
                {
                    sstream << "P2";
                    break;
                }
                case GridSquare::P3:
                {
                    sstream << "P3";
                    break;
                }
                case GridSquare::P4:
                {
                    sstream << "P4";
                    break;
                }
            }

            return sstream.str();
        }
};