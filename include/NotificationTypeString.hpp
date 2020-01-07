#pragma once

#include "NotificationType.hpp"

#include <sstream>

class NotificationTypeString
{
    public:
        inline static std::string PrintNotificationTypeString(NotificationType nt)
        {
            std::stringstream sstream;
            switch (nt)
            {
                case NotificationType::JOIN:
                {
                    sstream << "JOIN";
                    break;
                }
                case NotificationType::LEAVE:
                {
                    sstream << "LEAVE";
                    break;
                }
                case NotificationType::MESSAGE:
                {
                    sstream << "MESSAGE";
                    break;
                }
                case NotificationType::EVASIVE:
                {
                    sstream << "EVASIVE";
                    break;
                }
                case NotificationType::SILENT:
                {
                    sstream << "SILENT";
                    break;
                }
                case NotificationType::UNKNOWN:
                {
                    sstream << "UNKNOWN";
                    break;
                }
            }

            return sstream.str();
        }
};