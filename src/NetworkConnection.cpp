#include "NetworkConnection.hpp"

#include "spdlog/spdlog.h"

NetworkConnection::NetworkConnection(std::string nodeName)
:   mNodeName(nodeName)
{
    spdlog::get("console")->info("NetworkConnection::NetworkConnection {}", mNodeName);

    // czmq sets the signal handler internally
    // we want to override that
    zsys_handler_set(NULL);

    mNode = zyre_new(mNodeName.c_str());
    if ( !mNode )
    {
        spdlog::get("stderr")->error("NetworkConnection::NetworkConnection - Error.");
    }
}

NetworkConnection::~NetworkConnection()
{
    spdlog::get("console")->info("NetworkConnection::~NetworkConnection");

    zyre_destroy(&mNode);
}

zyre_t* NetworkConnection::Get()
{
    return mNode;
}