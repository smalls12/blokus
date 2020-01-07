#include "RegisterForGame.hpp"

RegisterForGame::RegisterForGame(INetworkSend& send, IRegisterRequest& request, IRegisterMessage& message)
:   mSend(send),
    mRegisterRequest(request),
    mRegisterMessage(message)
{
    spdlog::get("console")->debug("RegisterForGame::RegisterForGame");
}

RegisterForGame::~RegisterForGame()
{
    spdlog::get("console")->debug("RegisterForGame::~RegisterForGame");
}

bool RegisterForGame::Register(std::string gameName)
{
    spdlog::get("console")->debug("RegisterForGame::Register() - Start");

    std::string message = mRegisterMessage.BuildRegistrationRequestMessage(mRegisterRequest);
    mSend.Send( gameName, message );




    // // build message
    // blokus::Message request = Message::BuildBaseMessage(uuid);
    // Message::BuildRegisterReq(request, username);

    // // send to server
    // // serialize the protobuf message
    // size_t size = request.ByteSizeLong(); 
    // void *buffer = malloc(size);
    // request.SerializeToArray(buffer, size);

    // mSend.Send( mGameName, std::string((char *)buffer) );
    // // int rc = 0;
    // // rc = zyre_shouts(mConnection.Get(), mGameName.c_str(), "%s", (char *)buffer);

    spdlog::get("console")->debug("RegisterForGame::Register() - Done");

    return true;
}
