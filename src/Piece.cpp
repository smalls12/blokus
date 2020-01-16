#include "Piece.hpp"

#include "spdlog/spdlog.h"

Piece::Piece(Point offset, Padding padding, Layout layout, PieceType type)
:   mOffset(offset),
    mPadding(padding),
    mLayout(layout),
    mType(type)
{
    // spdlog::get("console")->info("Piece::Piece()");
}

Piece::Piece()
{
    // spdlog::get("console")->info("Piece::Piece()");

}

Piece::~Piece()
{
    // spdlog::get("console")->info("Piece::~Piece()");

}