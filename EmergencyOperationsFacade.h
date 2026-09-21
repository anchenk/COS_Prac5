#ifndef EMERGENCYOPERATIONSFACADE_H
#define EMERGENCYOPERATIONSFACADE_H

#include "AccessControlSystem.h"
#include "AlertService.h"
#include "INotificationChannel.h"

#include <string>

class EmergencyOperationsFacade
{
private:
  AccessControlSystem &accessControl;
  AlertService &alertService;
  INotificationChannel &notificationChannel;

public:
  EmergencyOperationsFacade(
      AccessControlSystem &access,
      AlertService &alerts,
      INotificationChannel &notifications) : accessControl(access), alertService(alerts), notificationChannel(notifications) {}

  bool initiateEvacuation(
      const std::string &area,
      const std::string &reason)
  {

    if (area.empty() || reason.empty())
    {
      std::cout << "[Facade] Evacuation rejected: " << "area and reason are required" << std::endl;

      return false;
    }

    std::cout << "\n[Facade] Starting evacuation workflow for " << area << std::endl;

    accessControl.restrictArea(area);
    accessControl.openEmergencyExits(area);
    alertService.issueEmergencyAlert(area, "Evacuate immediately. Reason: " + reason);

    bool notificationSent = notificationChannel.sendNotification(area, "Evacuate acitivated. Reason: " + reason, NotificationPriority::CRITICAL);

    if (!notificationSent)
    {
      std::cout << "[Facade] WARNING: "
                << "legacy notification failed" << std::endl;
      return false;
    }

    std::cout << "[Facade] Evacuation workflow completed successfully" << std::endl;

    return true;
  }

  bool endEvacuation(
      const std::string &area)
  {
    if (area.empty())
    {
      std::cout << "[Facade] End evacuation rejected: " << "area is required" << std::endl;
      return false;
    }

    std::cout << "\n[Facade] Ending evacuation workflow for " << area << std::endl;

    alertService.clearEmergencyAlert(area);
    accessControl.restoreNormalAccess(area);

    bool notificationSent = notificationChannel.sendNotification(area, "Evacuation ended. Normal operations may resume.", NotificationPriority::NORMAL);

    return notificationSent;
  }
};

#endif