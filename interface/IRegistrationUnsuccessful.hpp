#pragma once

/* =========================================================
 *
 * IUnsuccessfulRegistration.hpp
 * 
 * The options available for an unsuccesful registration
 * 
 * ========================================================= */

#include <string>

class IRegistrationUnsuccessful
{
    public:
        
        virtual std::string GetUsername() = 0;
        virtual std::string GetUuid() = 0;
};