#include "MessageProcessor.hpp"

#include "MessageType.hpp"
#include "ParseMessage.hpp"
#include "Register.hpp"

MessageProcessor::MessageProcessor(IRegisterMessage& message)
:   mMessage(message)
{
    spdlog::get("console")->info("MessageProcessor::MessageProcessor");
}

MessageProcessor::~MessageProcessor()
{
    spdlog::get("console")->info("MessageProcessor::MessageProcessor");
}

bool MessageProcessor::ProcessMessage(std::string data)
{
    MessageType mt = ParseMessage::ParseType(data);

    switch ( mt )
    {
        case MessageType::REGISTRATION_REQUEST:
        {
            Register r;
            mMessage.ParseRegistrationRequestMessage(data, r);
            mRegistrationRequestEndpoint(r);
            break;
        }
        case MessageType::REGISTRATION_RESPONSE:
        {
            Register successful;
            Register unsuccessful;

            bool success;
            success = mMessage.ParseRegistrationResponseMessage(data, successful, unsuccessful);
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
        default:
        {
            break;
        }
    }

    return true;
}



