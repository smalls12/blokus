#pragma once

#include "NetworkConnection.hpp"
#include "GameNotification.hpp"

#include "spdlog/spdlog.h"

class ReadGameNotification
{
    public:
        ReadGameNotification(NetworkConnection& connection, std::string gameName);
        ~ReadGameNotification();

        bool CheckEvent();

        // overload function call
        GameNotification operator()()
        {
            spdlog::get("console")->trace("ReadGameNotification::operator() - Start");

            zyre_event_t *event = zyre_event_new( mConnection.Get() );
            if( event )
            {
                // zyre_event_print( event );

                const char *value = zyre_event_group(event);
                if( value )
                {
                    std::string group(value);
                    spdlog::get("console")->trace("ReadGameNotification::operator() - Notification from Group {}", group);

                    if( group != mGameName )
                    {
                        spdlog::get("console")->warn("ReadGameNotification::operator() - Not a notification for this game.");
                        return GameNotification(std::string(), std::string(), NotificationType::UNKNOWN, std::string());
                    }
                }

                std::string name(zyre_event_peer_name( event ));
                std::string uuid(zyre_event_peer_uuid( event ));

                // event type
                const char *type = zyre_event_type(event);
                NotificationType nt = NotificationType::UNKNOWN;
                if (streq(type, "JOIN"))
                {
                    nt = NotificationType::JOIN;
                }
                else if (streq(type, "LEAVE"))
                {
                    nt = NotificationType::LEAVE;
                }
                else if (streq(type, "SHOUT"))
                {
                    nt = NotificationType::SHOUT;
                }
                else if (streq(type, "WHISPER"))
                {
                    nt = NotificationType::WHISPER;
                }
                else if (streq(type, "ENTER"))
                {
                    nt = NotificationType::ENTER;
                }
                else if (streq(type, "EXIT"))
                {
                    nt = NotificationType::EXIT;
                }
                else if (streq(type, "EVASIVE"))
                {
                    nt = NotificationType::EVASIVE;
                }
                else if (streq(type, "SILENT"))
                {
                    nt = NotificationType::SILENT;
                }
                else if (streq(type, "STOP"))
                {
                    nt = NotificationType::STOP;
                }

                // event data
                // only pertains to SHOUT and WHISPER
                std::string data;
                switch(nt)
                {
                    case NotificationType::SHOUT:
                    case NotificationType::WHISPER:
                    {
                        zmsg_t *msg = zyre_event_get_msg(event);
                        char *raw = zmsg_popstr(msg);
                        data = std::string(raw);
                        zmsg_destroy (&msg);
                        free (raw);
                        break;
                    }
                    case NotificationType::JOIN:
                    case NotificationType::LEAVE:
                    case NotificationType::ENTER:
                    case NotificationType::EXIT:
                    case NotificationType::EVASIVE:
                    case NotificationType::SILENT:
                    case NotificationType::STOP:
                    default:
                        break;
                }

                zyre_event_destroy( &event );

                spdlog::get("console")->trace("ReadGameNotification::operator() - Done");   

                return GameNotification(name, uuid, nt, data);
            }

            spdlog::get("console")->trace("ReadGameNotification::operator() - Done");

            return GameNotification(std::string(), std::string(), NotificationType::UNKNOWN, std::string());
        }

    private:
        NetworkConnection&  mConnection;
        std::string         mGameName;

        zpoller_t *mPoller;
};