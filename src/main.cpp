#include <iostream>
#include "../include/incident/IncidentCoordinator.h"
#include "../include/commands/OperatorConsole.h"
#include "../include/facade/AccessControlSystem.h"
#include "../include/facade/AlertService.h"
#include "../include/facade/EmergencyOperationsFacade.h"
#include "../include/adapter/LegacySecurityGateway.h"

// TODO(shared): This is where Scenario 1 (Ancheen) and Scenario 2
// (Katlego) get wired together into one coherent run. Musa's
// IncidentCoordinator, Incident and State classes tie both scenarios
// together. Replace this stub once individual pieces compile.
int main() {
    std::cout << "CampusGuard skeleton - replace with real scenarios.\n";

    IncidentCoordinator coordinator;
    OperatorConsole console;

    AccessControlSystem access;
    LegacySecurityGateway legacyGateway;
    // TODO(Katlego): wrap legacyGateway in a LegacyGatewayAdapter that
    // implements INotificationChannel, pass that to AlertService instead.
    // AlertService alerts(&adapter);
    // EmergencyOperationsFacade facade(&access, &alerts, &coordinator);

    // TODO(Ancheen): build 2+ ResponseUnit instances, register them with
    // coordinator, create concrete Commands, submit() them via console.

    // TODO(Musa): create Incident instances, attach observers, drive
    // state transitions, including one illegal transition to
    // demonstrate the required failure case.

    return 0;
}
