#include "InitialMoveIndicator.hpp"

#include "spdlog/spdlog.h"

InitialMoveIndicator::InitialMoveIndicator()
:   mColors()
{
    spdlog::get("console")->info("InitialMoveIndicator::InitialMoveIndicator()");

    mColors.insert(std::pair<PlayerColor, bool>( PlayerColor::BLUE, false ));
    mColors.insert(std::pair<PlayerColor, bool>( PlayerColor::RED, false ));
    mColors.insert(std::pair<PlayerColor, bool>( PlayerColor::GREEN, false ));
    mColors.insert(std::pair<PlayerColor, bool>( PlayerColor::YELLOW, false ));
}

InitialMoveIndicator::~InitialMoveIndicator()
{
    spdlog::get("console")->info("InitialMoveIndicator::~InitialMoveIndicator()");
}

bool InitialMoveIndicator::Check(PlayerColor color)
{
    return mColors.at(color);
}

bool InitialMoveIndicator::Perform(PlayerColor color)
{
    spdlog::get("console")->info("InitialMoveIndicator::Perform()");

    if( !Check(color) )
    {
        mColors.at(color) = true;
    }
    else
    {
        return false;
    }
    
}