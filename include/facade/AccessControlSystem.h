#ifndef CAMPUSGUARD_ACCESSCONTROLSYSTEM_H
#define CAMPUSGUARD_ACCESSCONTROLSYSTEM_H

#include <map>
#include <string>
#include <iostream>

// TODO(Katlego): One of the subsystems the Facade coordinates.
// Must remain independently usable (client can call lockZone() etc.
// directly without going through the facade).
class AccessControlSystem
{
public:
    AccessControlSystem();
    ~AccessControlSystem();

    bool lockZone(const std::string &zoneId);
    bool unlockZone(const std::string &zoneId);
    bool restrictZone(const std::string &zoneId);

private:
    enum class ZoneState
    {
        LOCKED,
        UNLOCKED,
        RESTRICTED
    };

    std::map<std::string, ZoneState> zoneStates;
};

#endif // CAMPUSGUARD_ACCESSCONTROLSYSTEM_H
