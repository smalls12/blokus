#pragma once

#include "PlayerId.hpp"

#include <sstream>

class PlayerIdString
{
    public:
        inline static std::string PrintPlayerIdString(PlayerId id)
        {
            std::stringstream sstream;
            switch (id)
            {
                case PlayerId::PLAYER_ONE:
                {
                    sstream << "PLAYER_ONE";
                    break;
                }
                case PlayerId::PLAYER_TWO:
                {
                    sstream << "PLAYER_TWO";
                    break;
                }
                case PlayerId::PLAYER_THREE:
                {
                    sstream << "PLAYER_THREE";
                    break;
                }
                case PlayerId::PLAYER_FOUR:
                {
                    sstream << "PLAYER_FOUR";
                    break;
                }
                case PlayerId::UNASSIGNED:
                default:
                {
                    sstream << "UNASSIGNED";
                    break;
                }
            }

            return sstream.str();
        }
};