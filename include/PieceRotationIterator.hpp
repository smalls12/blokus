#pragma once

/* =========================================================
 *
 * PieceRotationIterator.hpp
 * 
 * Used to iterate through the PieceRotation enum
 * 
 * ========================================================= */

#include "PieceRotation.hpp"

#include <vector>

class PieceRotationIterator
{
    public:
        inline static std::vector<PieceRotation> GetIterator()
        {
            std::vector<PieceRotation> rotations {
                PieceRotation::ZERO_DEGREES,
                PieceRotation::NINETY_DEGREES,
                PieceRotation::ONE_HUNDRED_EIGHTY_DEGREES,
                PieceRotation::TWO_HUNDRED_SEVENTY_DEGREES
            };

            return rotations;
        }      

    private:
        PieceRotationIterator();
        ~PieceRotationIterator();
};