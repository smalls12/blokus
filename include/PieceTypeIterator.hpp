#pragma once

/* =========================================================
 *
 * PieceTypeIterator.hpp
 * 
 * Used to iterate through the PieceType enum
 * 
 * ========================================================= */

#include "PieceType.hpp"

#include <vector>

class PieceTypeIterator
{
    public:
        inline static std::vector<PieceType> GetIterator()
        {
            std::vector<PieceType> types{
                PieceType::I1,
                PieceType::I2,
                PieceType::V3,
                PieceType::I3,
                PieceType::O,
                PieceType::T4,
                PieceType::I4,
                PieceType::L4,
                PieceType::Z4,
                PieceType::L5,
                PieceType::T5,
                PieceType::V5,
                PieceType::N,
                PieceType::Z5,
                PieceType::I5,
                PieceType::P,
                PieceType::W,
                PieceType::U,
                PieceType::F,
                PieceType::X
                // PieceType::Y
            };

            return types;
        }      

    private:
        PieceTypeIterator();
        ~PieceTypeIterator();
};