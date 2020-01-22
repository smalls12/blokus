#include "Piece.hpp"

#include "CalculatePadding.hpp"

#include "spdlog/spdlog.h"

Piece::Piece(Layout layout)
:   mLayout(layout),
    mPadding(CalculatePadding::CalculatePaddingFromLayout(mLayout))
{
    // spdlog::get("console")->info("Piece::Piece()");
}

Piece::Piece(Layout layout, Padding padding)
:   mLayout(layout),
    mPadding(padding)
{
    // spdlog::get("console")->info("Piece::Piece()");
}

Piece::~Piece()
{
    // spdlog::get("console")->info("Piece::Piece()");
}

std::ostream& operator <<(std::ostream& outputStream, const Piece& p)
{
    outputStream << "\n===== Layout =====";
    outputStream << p.mLayout;
    outputStream << "\n===== Layout =====";

    return outputStream;
}