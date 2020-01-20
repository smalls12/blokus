#pragma once

#include "PieceType.hpp"

#include <sstream>

class PieceTypeString
{
    public:
        inline static std::string PrintPieceTypeString(PieceType type)
        {
            std::stringstream sstream;
            switch (type)
            {
                case PieceType::I5:
                {
                    sstream << "I5";
                    break;
                }
                case PieceType::N:
                {
                    sstream << "N";
                    break;
                }
                case PieceType::V5:
                {
                    sstream << "V5";
                    break;
                }
                case PieceType::T5:
                {
                    sstream << "T5";
                    break;
                }
                case PieceType::U:
                {
                    sstream << "U";
                    break;
                }
                case PieceType::L5:
                {
                    sstream << "L5";
                    break;
                }
                case PieceType::Y:
                {
                    sstream << "Y";
                    break;
                }
                case PieceType::Z5:
                {
                    sstream << "Z5";
                    break;
                }
                case PieceType::W:
                {
                    sstream << "W";
                    break;
                }
                case PieceType::P:
                {
                    sstream << "P";
                    break;
                }
                case PieceType::X:
                {
                    sstream << "X";
                    break;
                }
                case PieceType::Z4:
                {
                    sstream << "Z4";
                    break;
                }
                case PieceType::I4:
                {
                    sstream << "I4";
                    break;
                }
                case PieceType::L4:
                {
                    sstream << "L4";
                    break;
                }
                case PieceType::O:
                {
                    sstream << "O";
                    break;
                }
                case PieceType::T4:
                {
                    sstream << "T4";
                    break;
                }
                case PieceType::I3:
                {
                    sstream << "I3";
                    break;
                }
                case PieceType::V3:
                {
                    sstream << "V3";
                    break;
                }
                case PieceType::I2:
                {
                    sstream << "I2";
                    break;
                }
                case PieceType::I1:
                {
                    sstream << "I1";
                    break;
                }
                case PieceType::F:
                {
                    sstream << "F";
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