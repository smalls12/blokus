#include <gmock/gmock.h>

#include "INetworkReceive.hpp"

class MNetworkReceive : public INetworkReceive
{
    public:
        MOCK_METHOD0( Poll, bool() );
        // MOCK_METHOD2( Receive, bool(std::string groupName, GameNotification& notification) );
        MOCK_METHOD2( Receive, bool(std::string groupName, std::vector<std::string>& messages) );

};