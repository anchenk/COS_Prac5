#include "../../include/facade/AccessControlSystem.h"

// TODO(Katlego): implement zone locking behaviour.
AccessControlSystem::AccessControlSystem()
{
  std::cout << "AccessControlSystem initialized." << std::endl;
}
AccessControlSystem::~AccessControlSystem()
{
  std::cout << "AccessControlSystem destroyed." << std::endl;
}

bool AccessControlSystem::lockZone(const std::string &zoneId)
{
  if (zoneId.empty())
  {
    std::cout << "[AccessControlSystem] ERROR: Zone ID cannot be empty." << std::endl;
    return false;
  }
  zoneStates[zoneId] = ZoneState::LOCKED;

  std::cout << "[AccessControlSystem] Zone " << zoneId << " locked." << std::endl;
  return true;
}
bool AccessControlSystem::unlockZone(const std::string &zoneId)
{
  if (zoneId.empty())
  {
    std::cout << "[AccessControlSystem] ERROR: Zone ID cannot be empty." << std::endl;
    return false;
  }
  zoneStates[zoneId] = ZoneState::UNLOCKED;

  std::cout << "[AccessControlSystem] Zone " << zoneId << " unlocked." << std::endl;
  return true;
}
bool AccessControlSystem::restrictZone(const std::string &zoneId)
{
  if (zoneId.empty())
  {
    std::cout << "[AccessControlSystem] ERROR: Zone ID cannot be empty." << std::endl;
    return false;
  }
  zoneStates[zoneId] = ZoneState::RESTRICTED;

  std::cout << "[AccessControlSystem] Zone " << zoneId << " restricted." << std::endl;
  return true;
}
