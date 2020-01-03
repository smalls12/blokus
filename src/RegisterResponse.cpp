#include "RegisterResponse.hpp"

RegisterResponse::RegisterResponse(NetworkConnection& connection, std::string username, std::string gameName)
:   mConnection(connection),
    mUsername(username),
    mGameName(gameName)
{
    spdlog::get("console")->debug("RegisterResponse::RegisterResponse()");
}

RegisterResponse::~RegisterResponse()
{
    spdlog::get("console")->debug("RegisterResponse::~RegisterResponse()");
}

bool RegisterResponse::SendRegisterResponse(blokus::Message message)
{
    spdlog::get("console")->debug("RegisterResponse::SendRegisterResponse() - Start");

    // build message
    blokus::Message response = Message::BuildRegisterResp(PlayerColor::BLUE, 1, mUsername);
    response.set_uuid(message.uuid());

    // send to server
    // serialize the protobuf message
    size_t size = response.ByteSizeLong(); 
    void *buffer = malloc(size);
    response.SerializeToArray(buffer, size);

    int rc = 0;
    rc = zyre_shouts(mConnection.Get(), mGameName.c_str(), "%s", (char *)buffer);

    spdlog::get("console")->debug("RegisterResponse::SendRegisterResponse() - Done");

    return true;
}