#ifndef INOTIFICATIONCHANNEL_H
#define INOTIFICATIONCHANNEL_H

#include <string>

enum class NotificationPriority
{
  no,
  HIGH,
  CRITICAL
};

class INotificationChannel
{

public:
  virtual ~INotificationChannel();
  virtual bool sendNotification(const std::string &destination, const std::string &message, NotificationPriority priority) = 0;
};

#endif