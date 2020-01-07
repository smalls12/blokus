#pragma once

/* =========================================================
 *
 * ISuccessfulRegistration.hpp
 * 
 * The options available for a succesful registration
 * 
 * ========================================================= */

#include "PlayerColor.hpp"

#include <string>

class IRegistrationSuccessful
{
    public:
        // virtual void SetPlayerColor(PlayerColor color) = 0;
        virtual PlayerColor GetPlayerColor() = 0;

        // virtual void SetPlayerId(int Id) = 0;
        virtual int GetPlayerId() = 0;

        // virtual void SetUsername(std::string name) = 0;
        virtual std::string GetUsername() = 0;

        // virtual void SetUuid(std::string uuid) = 0;
        virtual std::string GetUuid() = 0;
};