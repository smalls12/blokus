#pragma once

/* =========================================================
 *
 * IRegisterMessage.hpp
 * 
 * Network layer abstraction
 * Building with reference to what I know I need from zyre
 * However should be abstract enough to replace with any
 * network technology
 * 
 * ========================================================= */

#include "IRegisterRequest.hpp"
#include "IRegistrationSuccessful.hpp"
#include "IRegistrationUnsuccessful.hpp"

#include <string>

class IRegisterMessage
{
    public:
        virtual std::string BuildRegistrationRequestMessage(IRegisterRequest& message) = 0;
        virtual std::string BuildRegistrationResponseMessage(IRegistrationSuccessful& message) = 0;
        virtual std::string BuildRegistrationResponseMessage(IRegistrationUnsuccessful& message) = 0;

        virtual bool ParseRegistrationRequestMessage(std::string message, IRegisterRequest& request) = 0;
        virtual bool ParseRegistrationResponseMessage(std::string message, IRegistrationSuccessful& sucessful, IRegistrationUnsuccessful& unsuccesful) = 0;

};