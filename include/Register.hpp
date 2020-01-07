#pragma once

#include "IRegisterRequest.hpp"
#include "IRegistrationSuccessful.hpp"
#include "IRegistrationUnsuccessful.hpp"

#include "PlayerColor.hpp"

#include "spdlog/spdlog.h"

class Register : public IRegisterRequest, public IRegistrationSuccessful, public IRegistrationUnsuccessful
{
    public:
        Register();
        ~Register();

        void SetPlayerColor(PlayerColor color) { mPlayerColor = color; }
        PlayerColor GetPlayerColor() { return mPlayerColor; }

        void SetPlayerId(int id) { mPlayerId = id; }
        int GetPlayerId() { return mPlayerId; }

        void SetUsername(std::string username) { mUsername = username; }
        std::string GetUsername() { return mUsername; }

        void SetUuid(std::string uuid) { mUuid = uuid; }
        std::string GetUuid() { return mUuid; }

        void SetError(std::string error) { mError = error; }
        std::string GetError() { return mError; }

        // Copy constructor 
        Register(const Register &r)
        {
            mPlayerColor = r.mPlayerColor;
            mPlayerId = r.mPlayerId;
            mUsername = r.mUsername;
            mUuid = r.mUuid;
            mError = r.mError;
        } 

    private:
        PlayerColor     mPlayerColor;
        int             mPlayerId;
        std::string     mUsername;
        std::string     mUuid;

        std::string     mError;
        
};