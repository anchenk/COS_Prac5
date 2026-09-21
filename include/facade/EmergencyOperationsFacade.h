#ifndef CAMPUSGUARD_EMERGENCYOPERATIONSFACADE_H
#define CAMPUSGUARD_EMERGENCYOPERATIONSFACADE_H

#include <string>
#include "AccessControlSystem.h"
#include "AlertService.h"

class IncidentCoordinator; // forward declaration

// TODO(Katlego): Facade participant. initiateEvacuation() must call
// 3+ subsystem operations in a controlled sequence (e.g. lock down
// non-exit zones, broadcast the alert, notify the mediator/coordinator
// so response units react). Subsystems above must still be callable
// directly by other parts of the app - the facade is a convenience
// entry point, not the only way in.
class EmergencyOperationsFacade {
public:
    EmergencyOperationsFacade(AccessControlSystem* access,
                                AlertService* alerts,
                                IncidentCoordinator* coordinator);
    ~EmergencyOperationsFacade();

    // Realistic multi-step workflow: >= 3 subsystem operations.
    bool initiateEvacuation(const std::string& zoneId, const std::string& message);

private:
    AccessControlSystem* access_;   // not owned
    AlertService* alerts_;          // not owned
    IncidentCoordinator* coordinator_; // not owned
};

#endif // CAMPUSGUARD_EMERGENCYOPERATIONSFACADE_H
