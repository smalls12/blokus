#pragma once

/* =========================================================
 *
 * PlayerMoveRequestData.hpp
 * 
 * Concrete implementation for that data to build the
 * player move request
 * 
 * ========================================================= */

#include "IPlayerMoveRequestData.hpp"

#include "PlayerId.hpp"
#include "PieceType.hpp"
#include "Point.hpp"

class PlayerMoveRequestData : public IPlayerMoveRequestData
{
    public:
        PlayerMoveRequestData();
        ~PlayerMoveRequestData();

        void SetPlayerId(PlayerId id) { mPlayerId = id; }
        PlayerId GetPlayerId() { return mPlayerId; }

        void SetPieceType(PieceType type) { mPieceType = type; }
        PieceType GetPieceType() { return mPieceType; }

        void SetLocation(Point location) { mLocation = location; }
        Point GetLocation() { return mLocation; }

    private:
        PlayerId    mPlayerId;
        PieceType   mPieceType;
        Point       mLocation;
};