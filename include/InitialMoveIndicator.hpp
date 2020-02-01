#pragma once

/* =========================================================
 *
 * InitialMoveIndicator.hpp
 * 
 * Indicates if the initial move has been made for a particular color
 * 
 * ========================================================= */

#include "PlayerColor.hpp"

#include <map>

class InitialMoveIndicator
{
    public:
        InitialMoveIndicator();
        ~InitialMoveIndicator();

        bool Check(PlayerColor color);
        bool Perform(PlayerColor color);

    private:
        std::map<PlayerColor, bool>     mColors;
};