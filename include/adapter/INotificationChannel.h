#ifndef CAMPUSGUARD_INOTIFICATIONCHANNEL_H
#define CAMPUSGUARD_INOTIFICATIONCHANNEL_H

#include <string>

// Adapter pattern TARGET interface - what CampusGuard wants to call.
// TODO(Katlego): implement LegacyCampusSecurityGateway (the adaptee,
// with a deliberately incompatible interface - e.g. sendRawSignal(int
// code, char* payload) - see LegacySecurityGateway.h) and an adapter
// class that implements THIS interface by translating into calls on
// the adaptee. Passthrough wrapping without translation is not enough.
class INotificationChannel {
public:
    virtual ~INotificationChannel() {}
    virtual bool sendAlert(const std::string& message, const std::string& targetZone) = 0;
};

#endif // CAMPUSGUARD_INOTIFICATIONCHANNEL_H
