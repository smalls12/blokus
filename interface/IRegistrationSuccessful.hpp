#pragma once

/* =========================================================
 *
 * ISuccessfulRegistration.hpp
 * 
 * The options available for a succesful registration
 * 
 * ========================================================= */

#include <string>

class IRegistrationSuccessful
{
    public:
        virtual std::string GetUsername() = 0;
        virtual std::string GetUuid() = 0;
};