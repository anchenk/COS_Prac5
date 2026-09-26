#include "../../include/facade/AlertService.h"

#include <iostream>

// TODO(Katlego): implement, routing through legacyChannel_ (the Adapter).
AlertService::AlertService(INotificationChannel *legacyChannel)
    : legacyChannel_(legacyChannel) {}

AlertService::~AlertService() {}

bool AlertService::broadcastAlert(const std::string &message, const std::string &zoneId)
{
    if (message.empty())
    {
        std::cout << "[AlertService] ERROR: Message cannot be empty." << std::endl;
        return false;
    }

    if (zoneId.empty())
    {
        std::cout << "[AlertService] ERROR: Zone ID cannot be empty." << std::endl;
        return false;
    }

    if (legacyChannel_ == nullptr)
    {
        std::cout << "[AlertService] ERROR: Notification channel is not set." << std::endl;
        return false;
    }

    std::cout << "[AlertService] Broadcasting alert to zone: " << zoneId << std::endl;

    bool sent = legacyChannel_->sendAlert(message, zoneId);

    if (!sent)
    {
        std::cout << "[AlertService] ERROR: Failed to send alert." << std::endl;
        return false;
    }

    return true;
}
