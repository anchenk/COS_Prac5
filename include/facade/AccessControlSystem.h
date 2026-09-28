#ifndef CAMPUSGUARD_ACCESSCONTROLSYSTEM_H
#define CAMPUSGUARD_ACCESSCONTROLSYSTEM_H

#include <string>
#include <map>

// TODO(Katlego): One of the subsystems the Facade coordinates.
// Must remain independently usable (client can call lockZone() etc.
// directly without going through the facade).
class AccessControlSystem
{
private:
    enum class ZoneState
    {
        LOCKED,
        UNLOCKED,
        RESTRICTED
    };

    std::map<std::string, ZoneState> zoneStates;

public:
    AccessControlSystem();
    ~AccessControlSystem();

    bool lockZone(const std::string &zoneId);
    bool unlockZone(const std::string &zoneId);
    bool restrictZone(const std::string &zoneId);
};

#endif // CAMPUSGUARD_ACCESSCONTROLSYSTEM_H
