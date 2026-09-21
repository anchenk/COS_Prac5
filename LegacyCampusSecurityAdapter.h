#ifndef LEGACYCAMPUSSECURITYADAPTER_H
#define LEGACYCAMPUSSECURITYADAPTER_H

#include "INotificationChannel.h"
#include "LegacyCampusSecurityGateway.h"

class LegacyCampusSecurityAdapter : public INotificationChannel
{
private:
  LegacyCampusSecurityGateway &legacyGateway;

  int translatePriority(NotificationPriority priority)
  {
    switch (priority)
    {
    case NotificationPriority::NORMAL:
      return 1;
    case NotificationPriority::HIGH:
      return 2;
    case NotificationPriority::CRITICAL:
      return 3;
    default:
      return 1;
    }
  }

public:
  explicit LegacyCampusSecurityAdapter(LegacyCampusSecurityGateway &gateway) : legacyGateway(gateway) {}

  bool sendNotification(const std::string &destination, const std::string &message, NotificationPriority priority) override
  {
    int priorityCode = translatePriority(priority);
    std::string packedMessage = destination + ":" + message;

    return legacyGateway.sendLegacyPacket(packedMessage.c_str(), priorityCode) == 0;
  }
};

#endif