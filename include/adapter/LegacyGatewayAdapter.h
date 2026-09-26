#ifndef CAMPUSGUARD_LEGACYGATEWAYADAPTER_H
#define CAMPUSGUARD_LEGACYGATEWAYADAPTER_H

#include "INotificationChannel.h"
#include "LegacySecurityGateway.h"

#include <map>
#include <string>

class LegacyGatewayAdapter : public INotificationChannel
{
public:
  LegacyGatewayAdapter();
  virtual ~LegacyGatewayAdapter();

  bool sendAlert(
      const std::string &message,
      const std::string &targetZone) override;

private:
  LegacySecurityGateway gateway_;

  std::map<std::string, int> zoneIds_;

  int nextZoneId_;

  int translateZone(
      const std::string &targetZone);

  int determineSignalCode(
      const std::string &message) const;
};

#endif // CAMPUSGUARD_LEGACYGATEWAYADAPTER_H