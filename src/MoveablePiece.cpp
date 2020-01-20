#include "MoveablePiece.hpp"

#include "spdlog/spdlog.h"

MoveablePiece::MoveablePiece(Piece piece)
:   Piece(piece),
    mLocation(Point(0, 0))
{
    // spdlog::get("console")->info("Piece::Piece()");
}

MoveablePiece::MoveablePiece(Layout layout, Padding padding)
:   Piece(Piece(layout, padding)),
    mLocation(Point(0, 0))
{
    // spdlog::get("console")->info("Piece::Piece()");
}

MoveablePiece::~MoveablePiece()
{
    // spdlog::get("console")->info("Piece::Piece()");

}

std::ostream& operator <<(std::ostream& outputStream, const MoveablePiece& p)
{
    outputStream << "\n===== Location =====\n";
    outputStream << p.mLocation;
    outputStream << "\n===== Location =====\n";

    outputStream << "\n===== Layout =====\n";
    outputStream << p.mLayout;
    outputStream << "\n===== Layout =====\n";

    return outputStream;
}