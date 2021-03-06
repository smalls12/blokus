#pragma once

// this file helps build messages for transport

// protobuf header
#include <protobuf/blokus.pb.h>

#include "MessageType.hpp"

class ParseMessage
{
    public:
        inline static MessageType ParseType(std::string message)
        {
            blokus::Message in;
            in.ParseFromString(message);

            MessageType mt = MessageType::UNKNOWN;
            switch( in.type() )
            {
                case blokus::Message::REQUEST:
                {
                    switch( in.request().type() )
                    {
                        case blokus::REGISTER:
                        {
                            mt = MessageType::REGISTRATION_REQUEST;
                            break;
                        }
                        case blokus::START_GAME:
                        {
                            mt = MessageType::STARTGAME_REQUEST;
                            break;
                        }
                        case blokus::PLAYER_MOVE:
                        {
                            mt = MessageType::PLAYERMOVE_REQUEST;
                            break;
                        }
                        case blokus::CHAT:
                        {
                            mt = MessageType::CHAT_REQUEST;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case blokus::Message::RESPONSE:
                {
                    switch( in.response().type() )
                    {
                        case blokus::REGISTER:
                        {
                            mt = MessageType::REGISTRATION_RESPONSE;
                            break;
                        }
                        case blokus::START_GAME:
                        {
                            mt = MessageType::STARTGAME_RESPONSE;
                            break;
                        }
                        case blokus::PLAYER_MOVE:
                        {
                            mt = MessageType::PLAYERMOVE_RESPONSE;
                            break;
                        }
                        case blokus::CHAT:
                        {
                            mt = MessageType::CHAT_RESPONSE;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }

            return mt; 
        };

    private:
        ParseMessage();
        ~ParseMessage(); 
};
