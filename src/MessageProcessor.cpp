#include "MessageProcessor.hpp"

#include "Message.hpp"

#include "MessageType.hpp"
#include "ParseMessage.hpp"
#include "Register.hpp"

MessageProcessor::MessageProcessor()
:   mRegistrationRequestEndpoint(),
    mRegistrationSuccessfulEndpoint(),
    mRegistrationUnsuccessfulEndpoint(),
    mStartGameEndpoint(),
    mPlayerMoveEndpoint()
{
    spdlog::get("console")->info("MessageProcessor::MessageProcessor()");
}

MessageProcessor::~MessageProcessor()
{
    spdlog::get("console")->info("MessageProcessor::~MessageProcessor()");
}

bool MessageProcessor::ProcessMessage(std::string data)
{
    spdlog::get("console")->info("MessageProcessor::ProcessMessage() - Start");

    MessageType mt = ParseMessage::ParseType(data);

    switch ( mt )
    {
        case MessageType::REGISTRATION_REQUEST:
        {
            Register r;

            Message m;
            m.ParseRegistrationRequestMessage(data, r);
            mRegistrationRequestEndpoint(r);
            break;
        }
        case MessageType::REGISTRATION_RESPONSE:
        {
            Register successful;
            Register unsuccessful;

            Message m;

            bool success;
            success = m.ParseRegistrationResponseMessage(data, successful, unsuccessful);
            if( success )
            {
                mRegistrationSuccessfulEndpoint(successful);
            }
            else
            {
                mRegistrationUnsuccessfulEndpoint(unsuccessful);
            }

            break;
        }
        case MessageType::STARTGAME_REQUEST:
        case MessageType::STARTGAME_RESPONSE:
        {
            Message m;
            m.ParseStartGameRequestMessage(data);
            mStartGameEndpoint();
            break;
        }
        case MessageType::PLAYERMOVE_REQUEST:
        case MessageType::PLAYERMOVE_RESPONSE:
        {
            Message m;
            m.ParsePlayerMoveRequestMessage(data);
            mPlayerMoveEndpoint();
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}



