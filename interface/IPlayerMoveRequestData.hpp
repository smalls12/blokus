#pragma once

#include "PlayerId.hpp"
#include "PieceType.hpp"
#include "PieceRotation.hpp"
#include "Point.hpp"

#include <string>

class IPlayerMoveRequestData
{
    public:

        virtual void SetPlayerId(PlayerId id) = 0;
        virtual PlayerId GetPlayerId() = 0;

        virtual void SetPieceType(PieceType type) = 0;
        virtual PieceType GetPieceType() = 0;

        virtual void SetPieceRotation(PieceRotation rotation) = 0;
        virtual PieceRotation GetPieceRotation() = 0;

        virtual void SetPieceFlipped(bool flipped) = 0;
        virtual bool GetPieceFlipped() = 0;

        virtual void SetLocation(Point location) = 0;
        virtual Point GetLocation() = 0;
};