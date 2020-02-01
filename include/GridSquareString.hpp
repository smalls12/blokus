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
                case GridSquare::INVALID:
                {
                    sstream << "INVALID";
                    break;
                }
                case GridSquare::PLAYER_ONE:
                {
                    sstream << "PLAYER_ONE";
                    break;
                }
                case GridSquare::PLAYER_TWO:
                {
                    sstream << "PLAYER_TWO";
                    break;
                }
                case GridSquare::PLAYER_THREE:
                {
                    sstream << "PLAYER_THREE";
                    break;
                }
                case GridSquare::PLAYER_FOUR:
                {
                    sstream << "PLAYER_FOUR";
                    break;
                }
                default:
                {
                    sstream << "UNKNOWN";
                    break;
                }
            }

            return sstream.str();
        }
};