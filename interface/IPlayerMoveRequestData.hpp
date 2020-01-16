#pragma once

#include "PieceType.hpp"
#include "Point.hpp"

#include <string>

class IPlayerMoveRequestData
{
    public:

        virtual void SetPlayerId(int id) = 0;
        virtual int GetPlayerId() = 0;

        virtual void SetPieceType(PieceType type) = 0;
        virtual PieceType GetPieceType() = 0;

        virtual void SetLocation(Point location) = 0;
        virtual Point GetLocation() = 0;
};