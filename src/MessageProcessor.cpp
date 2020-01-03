#include "MessageProcessor.hpp"

MessageProcessor::MessageProcessor()
:   mReceiveEndpoints(),
    mResponseEndpoints(),
    mEndpointsMutex()
{
    spdlog::get("console")->info("MessageProcessor::MessageProcessor");
}

MessageProcessor::~MessageProcessor()
{
    spdlog::get("console")->info("MessageProcessor::MessageProcessor");
}

bool MessageProcessor::ProcessMessage(std::string data)
{
    std::unique_lock<std::mutex> lock(mEndpointsMutex);

    blokus::Message in;
    in.ParseFromString(data);

    if (in.type() == blokus::Message::REQUEST)
    {
        bool ret = false;
        blokus::Message out;
        ret = ProcessRequest(in, out);
        if( ret )
        {
            return ProcessResponse(in);
        }
        else
        {
            ProcessResponse(in);
        }
        return ret;
    }
    else if (in.type() == blokus::Message::RESPONSE)
    {
        return ProcessResponse(in);
    }
    else
    {
        spdlog::get("console")->debug("MessageProcessor::ProcessMessage() - Invalid message");
        return false;
    }
}

bool MessageProcessor::ProcessRequest(blokus::Message in, blokus::Message& out)
{
    std::map<blokus::Type, std::function<bool(blokus::Message, blokus::Message&)>>::iterator it;

    it = mReceiveEndpoints.find(in.request().type());
    if (it != mReceiveEndpoints.end())
    {
        return mReceiveEndpoints[in.request().type()](in, out);
    }
    else
    {
        spdlog::get("stderr")->debug("MessageProcessor::ProcessRequest() - No endpoint set.");
        return false;
    }
}

bool MessageProcessor::ProcessResponse(blokus::Message out)
{
    std::map<blokus::Type, std::function<bool(blokus::Message)>>::iterator it;

    it = mResponseEndpoints.find(out.response().type());
    if (it != mResponseEndpoints.end())
    {
        return mResponseEndpoints[out.response().type()](out);
    }
    else
    {
        spdlog::get("stderr")->debug("MessageProcessor::ProcessResponse() - No endpoint set.");
        return false;
    }
}

bool MessageProcessor::SetReceiveEndpoint(blokus::Type type, std::function<bool(blokus::Message, blokus::Message&)> func)
{
    std::unique_lock<std::mutex> lock(mEndpointsMutex);
    std::pair<std::map<blokus::Type, std::function<bool(blokus::Message, blokus::Message&)>>::iterator,bool> ret;
    ret = mReceiveEndpoints.insert( std::pair<blokus::Type, std::function<bool(blokus::Message, blokus::Message&)>>(type, func) );
    return ret.second;
}

bool MessageProcessor::SetResponseEndpoint(blokus::Type type, std::function<bool(blokus::Message)> func)
{
    std::unique_lock<std::mutex> lock(mEndpointsMutex);
    std::pair<std::map<blokus::Type, std::function<bool(blokus::Message)>>::iterator,bool> ret;
    ret = mResponseEndpoints.insert( std::pair<blokus::Type, std::function<bool(blokus::Message)>>(type, func) );
    return ret.second;
}