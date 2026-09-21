#ifndef CAMPUSGUARD_ALERTSERVICE_H
#define CAMPUSGUARD_ALERTSERVICE_H

#include <string>
#include "../adapter/INotificationChannel.h"

// TODO(Katlego): Another subsystem the Facade coordinates. Uses the
// Adapter (INotificationChannel*) to reach the legacy gateway alongside
// any modern channels. Must remain independently usable.
class AlertService {
public:
    explicit AlertService(INotificationChannel* legacyChannel);
    ~AlertService();

    bool broadcastAlert(const std::string& message, const std::string& zoneId);

private:
    INotificationChannel* legacyChannel_; // not owned, or owned - decide and document
};

#endif // CAMPUSGUARD_ALERTSERVICE_H
