#include "../../include/facade/EmergencyOperationsFacade.h"

// TODO(Katlego): implement initiateEvacuation to call >= 3 subsystem
// operations in sequence (e.g. access_->lockZone, alerts_->broadcastAlert,
// coordinator interaction).
EmergencyOperationsFacade::EmergencyOperationsFacade(AccessControlSystem* access,
                                                        AlertService* alerts,
                                                        IncidentCoordinator* coordinator)
    : access_(access), alerts_(alerts), coordinator_(coordinator) {}

EmergencyOperationsFacade::~EmergencyOperationsFacade() {}

bool EmergencyOperationsFacade::initiateEvacuation(const std::string& zoneId, const std::string& message) {
    // TODO: implement the multi-step workflow
    return false;
}
