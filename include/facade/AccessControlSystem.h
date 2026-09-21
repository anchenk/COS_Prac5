#ifndef CAMPUSGUARD_ACCESSCONTROLSYSTEM_H
#define CAMPUSGUARD_ACCESSCONTROLSYSTEM_H

#include <string>

// TODO(Katlego): One of the subsystems the Facade coordinates.
// Must remain independently usable (client can call lockZone() etc.
// directly without going through the facade).
class AccessControlSystem {
public:
    AccessControlSystem();
    ~AccessControlSystem();

    bool lockZone(const std::string& zoneId);
    bool unlockZone(const std::string& zoneId);
    bool restrictZone(const std::string& zoneId);
};

#endif // CAMPUSGUARD_ACCESSCONTROLSYSTEM_H
