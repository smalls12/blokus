#include "MoveablePiece.hpp"

#include "spdlog/spdlog.h"

MoveablePiece::MoveablePiece(Piece piece)
:   Piece(piece),
    mLocation(Point(0, 0)),
    mPlayed(false)
{
    // spdlog::get("console")->info("Piece::Piece()");
}

MoveablePiece::MoveablePiece(Layout layout, Padding padding)
:   Piece(Piece(layout, padding)),
    mLocation(Point(0, 0)),
    mPlayed(false)
{
    // spdlog::get("console")->info("Piece::Piece()");
}

MoveablePiece::~MoveablePiece()
{
    // spdlog::get("console")->info("Piece::Piece()");

}

std::ostream& operator <<(std::ostream& outputStream, const MoveablePiece& p)
{
    outputStream << "\n===== ID =====\n";
    outputStream << &p;
    outputStream << "\n===== ID =====\n";

    outputStream << "\n===== Location =====\n";
    outputStream << p.mLocation;
    outputStream << "\n===== Location =====\n";

    outputStream << "\n===== Layout =====\n";
    outputStream << p.mLayout;
    outputStream << "\n===== Layout =====\n";

    outputStream << "\n===== Played =====\n";
    if( p.mPlayed )
    {
        outputStream << "YES";
    }
    else
    {
        outputStream << "NO";
    }
    outputStream << "\n===== Played =====\n";

    return outputStream;
}