#pragma once

#include "IRegisterRequest.hpp"
#include "IRegistrationSuccessful.hpp"
#include "IRegistrationUnsuccessful.hpp"

#include "spdlog/spdlog.h"

class Register : public IRegisterRequest, public IRegistrationSuccessful, public IRegistrationUnsuccessful
{
    public:
        Register();
        ~Register();

        void SetUsername(std::string username) { mUsername = username; }
        std::string GetUsername() { return mUsername; }

        void SetUuid(std::string uuid) { mUuid = uuid; }
        std::string GetUuid() { return mUuid; }

        void SetError(std::string error) { mError = error; }
        std::string GetError() { return mError; }

        // Copy constructor 
        Register(const Register &r)
        {
            mUsername = r.mUsername;
            mUuid = r.mUuid;
            mError = r.mError;
        } 

    private:
        std::string     mUsername;
        std::string     mUuid;
        std::string     mError;
};