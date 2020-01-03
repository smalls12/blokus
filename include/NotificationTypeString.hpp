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
                case NotificationType::SHOUT:
                {
                    sstream << "SHOUT";
                    break;
                }
                case NotificationType::WHISPER:
                {
                    sstream << "WHISPER";
                    break;
                }
                case NotificationType::ENTER:
                {
                    sstream << "ENTER";
                    break;
                }
                case NotificationType::EXIT:
                {
                    sstream << "EXIT";
                    break;
                }
                case NotificationType::LEADER:
                {
                    sstream << "LEADER";
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
                case NotificationType::STOP:
                {
                    sstream << "STOP";
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