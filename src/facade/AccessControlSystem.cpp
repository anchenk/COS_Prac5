#include "../../include/facade/AccessControlSystem.h"

// TODO(Katlego): implement zone locking behaviour.
AccessControlSystem::AccessControlSystem() {}
AccessControlSystem::~AccessControlSystem() {}

bool AccessControlSystem::lockZone(const std::string& zoneId) { return false; }
bool AccessControlSystem::unlockZone(const std::string& zoneId) { return false; }
bool AccessControlSystem::restrictZone(const std::string& zoneId) { return false; }
