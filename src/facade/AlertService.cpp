#include "../../include/facade/AlertService.h"

// TODO(Katlego): implement, routing through legacyChannel_ (the Adapter).
AlertService::AlertService(INotificationChannel* legacyChannel)
    : legacyChannel_(legacyChannel) {}

AlertService::~AlertService() {}

bool AlertService::broadcastAlert(const std::string& message, const std::string& zoneId) {
    // TODO: call legacyChannel_->sendAlert(message, zoneId) plus any
    // modern channels
    return false;
}
