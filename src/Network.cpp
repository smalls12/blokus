#include <string>

/* =========================================================
 *
 * Implements the network layer
 * 
 * ========================================================= */

#include "Network.hpp"

#include "spdlog/spdlog.h"

Network::Network(std::string nodeName, ICompress& compress, IDecompress& decompress)
:   mNodeName(nodeName),
    mCompression(compress),
    mDecompression(decompress)
{
    spdlog::get("console")->info("Network::Network() - Node {}", mNodeName);
}

Network::~Network()
{
    spdlog::get("console")->info("Network::~Network()");
}

// Connect into the network
bool Network::Connect()
{
    spdlog::get("console")->info("Network::Connect()");

    // czmq sets the signal handler internally
    // we want to override that
    zsys_handler_set(NULL);

    mNode = zyre_new(mNodeName.c_str());
    if ( !mNode )
    {
        spdlog::get("stderr")->error("Network::Connect() - Error.");
    }

    mPoller = zpoller_new(zyre_socket(mNode), NULL);
}

// Disconnect from the network
void Network::Disconnect()
{
    spdlog::get("console")->info("Network::Disconnect()");

    zpoller_destroy(&mPoller);

    zyre_destroy(&mNode);
}

bool Network::Start()
{
    int rc = 0;
    rc = zyre_start(mNode);
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("Network::JoinGroup() - Could not start node.");
        return false;
    }
    return true;
}

void Network::Stop()
{
    zyre_stop(mNode);
}

// Disconnect from the network
bool Network::Configure(std::string parameter)
{
    spdlog::get("console")->info("Network::Configure()");

    zyre_set_header(mNode, "X-BLOKUS", "%s", parameter.c_str());
}

// Retrieve the name of the network
std::string Network::GetName()
{
    spdlog::get("console")->info("Network::GetName()");

    return std::string( zyre_name( mNode ) );
}

// Retrieve the unique identifier of the network
std::string Network::GetUniqueIdentifier()
{
    spdlog::get("console")->info("Network::GetUniqueIdentifier()");

    return std::string( zyre_uuid( mNode ) );
}

// Join a network lobby
bool Network::JoinGroup(std::string groupName)
{
    spdlog::get("console")->info("Network::JoinGroup()");

    int rc = 0;
    rc = zyre_join(mNode, groupName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("Network::JoinGroup() - Could not join game.");
    }

    zclock_sleep(250);
}

// Leave a network lobby
bool Network::LeaveGroup(std::string groupName)
{
    spdlog::get("console")->info("Network::LeaveGroup()");

    int rc = 0;
    rc = zyre_leave(mNode, groupName.c_str());
    if ( rc != 0 )
    {
        spdlog::get("stderr")->error("Network::LeaveGroup() - Could not leave group.");
    }
}

// Send to the network
int Network::Send(std::string groupName, std::string message)
{
    spdlog::get("console")->info("Network::Compressing message");

    std::string compressed;
    mCompression.Compress(message, compressed);

    const char* c_compressed = compressed.c_str();
    spdlog::get("console")->info("Network::Sending message size {}", compressed.size());

    int rc = 0;
    // rc = zyre_shouts(mNode, groupName.c_str(), "%s", c_compressed);

    zmsg_t *msg = zmsg_new();
    rc = zmsg_addmem(msg, compressed.c_str(), compressed.size());
    rc = zyre_shout(mNode, groupName.c_str(), &msg);

    return rc;
}

// Send to the network
bool Network::Poll()
{
    spdlog::get("console")->trace("Network::Poll()");

    zsock_t *which = (zsock_t *)zpoller_wait(mPoller, 0);
    if( !which )
    {
        // spdlog::get("stderr")->error("ReadGameNotification::operator() - No event.");
        return false;
    }

    // zpoller_expired
    // zpoller_terminated

    return true;
}

// Receive from the network
bool Network::Receive(std::string groupName, std::vector<std::string>& messages)
{
    spdlog::get("console")->info("Network::Receive()");

    zyre_event_t *event = zyre_event_new( mNode );
    if( event )
    {
        zyre_event_print( event );

        const char *value = zyre_event_group(event);
        if( value )
        {
            std::string group(value);
            spdlog::get("console")->trace("Network::Receive() - Notification from Group {}", group);

            if( group != groupName )
            {
                spdlog::get("console")->warn("Network::Receive() - Not a notification for this game.");
                return false;
            }
        }
        else
        {
            spdlog::get("stderr")->warn("Network::Receive() - Not a notification for this game.");
            return false;
        }

        messages.push_back( std::string( zyre_event_peer_name( event ) ) );
        messages.push_back( std::string( zyre_event_peer_uuid( event ) ) );
        std::string type( zyre_event_type( event ) );
        spdlog::get("console")->info("Network::Receive() - Type {}", type);

        messages.push_back( type );

        zmsg_t *msg = zyre_event_get_msg( event );
        if( msg )
        {
            // spdlog::get("console")->info("Network::Message, raw size {}", zmsg_content_size(msg));
            size_t raw_size = zmsg_content_size( msg );
            char *raw_data = zmsg_popstr( msg );
            if( raw_data )
            {
                std::string raw_string( raw_data, raw_size );
                free( raw_data );

                std::string decompressed;
                mDecompression.Decompress(raw_string, decompressed);

                messages.push_back( decompressed );
            }
            else
            {
                spdlog::get("console")->trace("Network::Receive() - 4");
                messages.push_back( std::string( std::string("") ) );
            }
            zmsg_destroy( &msg );
        }
        else
        {
            messages.push_back( std::string( std::string("") ) );
        }

        zyre_event_destroy( &event );

        spdlog::get("console")->trace("Network::Receive() - Done");   

        return true;
    }
    else
    {
        spdlog::get("stderr")->error("Network::Receive() - Error");
        return false;
    }
}

// Search for lobbies on network
void Network::Search(std::vector<std::pair<std::string, std::string>>& lobbies)
{
    spdlog::get("console")->trace("Network::Search()");

    zlist_t* peers = zyre_peers(mNode);
    while(zlist_size(peers) > 0)
    {
        char *uuid;
        uuid = (char *)zlist_pop (peers);
        spdlog::get("console")->trace("Network::Search() - Peer {}", uuid);

        char *value = zyre_peer_header_value(mNode, uuid, "X-BLOKUS");
        if( value )
        {
            std::string header(value);
            zstr_free(&value);
            spdlog::get("console")->trace("Network::Search() - Header Value {}", header);

            // std::shared_ptr<ActiveGame> ag;
            // if( !mActiveGameManager.GameAlreadyActive(header, ag) )
            // {
            //     ag = std::make_shared<ActiveGame>(std::string(header), std::string(uuid));
            //     mActiveGameManager.AddActiveGame(std::string(header), ag);
            // }
            lobbies.push_back(std::pair<std::string, std::string>(header, uuid));
        }
    }
    zlist_destroy (&peers);
}