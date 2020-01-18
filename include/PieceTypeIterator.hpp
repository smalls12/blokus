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
                PieceType::I5,
                PieceType::N,
                PieceType::V5,
                PieceType::T5,
                PieceType::U,
                PieceType::L5,
                PieceType::Y,
                PieceType::Z5,
                PieceType::W,
                PieceType::P,
                PieceType::X,
                PieceType::Z4,
                PieceType::I4,
                PieceType::L4,
                PieceType::O,
                PieceType::T4,
                PieceType::I3,
                PieceType::V3,
                PieceType::I2,
                PieceType::I1
            };

            return types;
        }      

    private:
        PieceTypeIterator();
        ~PieceTypeIterator();
};