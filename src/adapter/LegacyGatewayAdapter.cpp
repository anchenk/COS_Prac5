#include "LegacyGatewayAdapter.h"

#include <iostream>

LegacyGatewayAdapter::LegacyGatewayAdapter()
    : nextZoneId_(100)
{
  std::cout
      << "[LegacyGatewayAdapter] Adapter ready."
      << std::endl;
}

LegacyGatewayAdapter::~LegacyGatewayAdapter()
{
}

int LegacyGatewayAdapter::translateZone(
    const std::string &targetZone)
{
  std::map<std::string, int>::iterator it =
      zoneIds_.find(targetZone);

  if (it != zoneIds_.end())
  {
    return it->second;
  }

  int assignedId = nextZoneId_;

  zoneIds_[targetZone] = assignedId;

  ++nextZoneId_;

  std::cout
      << "[LegacyGatewayAdapter] Translating zone \""
      << targetZone
      << "\" -> legacy zone "
      << assignedId
      << std::endl;

  return assignedId;
}

int LegacyGatewayAdapter::determineSignalCode(
    const std::string &message) const
{
  if (message.find("EVACUATE") != std::string::npos ||
      message.find("Evacuate") != std::string::npos ||
      message.find("evacuate") != std::string::npos)
  {
    return 900;
  }

  if (message.find("FIRE") != std::string::npos ||
      message.find("Fire") != std::string::npos ||
      message.find("fire") != std::string::npos)
  {
    return 800;
  }

  // General emergency alert.
  return 500;
}

bool LegacyGatewayAdapter::sendAlert(
    const std::string &message,
    const std::string &targetZone)
{
  if (message.empty())
  {
    std::cout
        << "[LegacyGatewayAdapter] ERROR: "
        << "Alert message cannot be empty."
        << std::endl;

    return false;
  }

  if (targetZone.empty())
  {
    std::cout
        << "[LegacyGatewayAdapter] ERROR: "
        << "Target zone cannot be empty."
        << std::endl;

    return false;
  }

  int legacyZone =
      translateZone(targetZone);

  int signalCode =
      determineSignalCode(message);

  std::string payload =
      "CAMPUSGUARD|" + targetZone + "|" + message;

  std::cout
      << "[LegacyGatewayAdapter] Translating CampusGuard alert..."
      << std::endl;

  int result =
      gateway_.sendRawSignal(
          signalCode,
          payload.c_str(),
          legacyZone);

  return result == 0;
}