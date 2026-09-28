#include <iostream>
#include <string>

// ============================================================
// INCIDENT / STATE / OBSERVER
// ============================================================

#include "../include/incident/Incident.h"
#include "../include/incident/ReportedState.h"
#include "../include/incident/IncidentCoordinator.h"

#include "../include/observer/IIncidentObserver.h"

// ============================================================
// RESPONSE UNITS / MEDIATOR
// ============================================================

#include "../include/units/ResponseUnit.h"
#include "../include/units/SecurityTeam.h"
#include "../include/units/MedicalResponder.h"
#include "../include/units/FacilitiesCrew.h"

// ============================================================
// COMMAND
// ============================================================

#include "../include/commands/OperatorConsole.h"
#include "../include/commands/DispatchUnitCommand.h"
#include "../include/commands/LockdownZoneCommand.h"
#include "../include/commands/IssueAlertCommand.h"
#include "../include/commands/CancelActionCommand.h"

// ============================================================
// FACADE
// ============================================================

#include "../include/facade/AccessControlSystem.h"
#include "../include/facade/AlertService.h"
#include "../include/facade/EmergencyOperationsFacade.h"

// ============================================================
// ADAPTER
// ============================================================

#include "../include/adapter/LegacyGatewayAdapter.h"

// ============================================================
// TEST OBSERVER
// ============================================================
//
// This is a simple Observer used only to make the Observer behaviour
// clearly visible while testing.
//
// It implements IIncidentObserver and reacts whenever Incident calls
// notify().
//

class TestIncidentObserver : public IIncidentObserver
{
public:
    explicit TestIncidentObserver(const std::string &name)
        : name_(name)
    {
    }

    void onIncidentChanged(
        const Incident &incident,
        const std::string &reason) override
    {
        std::cout
            << "[OBSERVER - " << name_ << "] "
            << "Incident " << incident.getId()
            << " changed. Current state: "
            << incident.currentStateName()
            << ". Reason: "
            << reason
            << std::endl;
    }

private:
    std::string name_;
};

int main()
{
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "                  CAMPUSGUARD FULL TEST\n";
    std::cout << "============================================================\n\n";

    /*
     * ==========================================================
     * 1. CREATE SHARED SYSTEM OBJECTS
     * ==========================================================
     */

    std::cout << "------------------------------------------------------------\n";
    std::cout << "SETUP: Creating CampusGuard subsystems\n";
    std::cout << "------------------------------------------------------------\n";

    // Mediator
    IncidentCoordinator coordinator;

    // Command Invoker
    OperatorConsole console;

    // Facade subsystem
    AccessControlSystem access;

    // Adapter
    LegacyGatewayAdapter adapter;

    // AlertService talks to the Adapter through INotificationChannel
    AlertService alerts(&adapter);

    // Facade
    EmergencyOperationsFacade facade(
        &access,
        &alerts,
        &coordinator);

    std::cout << "\n[SETUP] Core subsystems created.\n";

    /*
     * ==========================================================
     * 2. MEDIATOR SETUP
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 1: MEDIATOR SETUP\n";
    std::cout << "------------------------------------------------------------\n";

    SecurityTeam security(
        "Security Alpha",
        &coordinator);

    MedicalResponder medical(
        "Medical Bravo",
        &coordinator);

    FacilitiesCrew facilities(
        "Facilities Charlie",
        &coordinator);

    coordinator.registerUnit(&security);
    coordinator.registerUnit(&medical);
    coordinator.registerUnit(&facilities);

    std::cout
        << "[TEST] Security, Medical and Facilities registered "
        << "with IncidentCoordinator.\n";

    /*
     * ==========================================================
     * 3. INCIDENT + STATE PATTERN
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 2: STATE PATTERN\n";
    std::cout << "------------------------------------------------------------\n";

    Incident fire(
        "INC-001",
        "Fire",
        "Library",
        4);

    fire.setState(
        new ReportedState());

    std::cout
        << "[STATE] Initial state: "
        << fire.currentStateName()
        << "\n";

    /*
     * Expected:
     *
     * Reported
     *      ->
     * Dispatched
     *      ->
     * Contained
     *      ->
     * Resolved
     */

    bool stateResult;

    stateResult = fire.advanceState();

    std::cout
        << "[STATE] advanceState() returned: "
        << (stateResult ? "true" : "false")
        << "\n";

    std::cout
        << "[STATE] Current state: "
        << fire.currentStateName()
        << "\n";

    stateResult = fire.advanceState();

    std::cout
        << "[STATE] advanceState() returned: "
        << (stateResult ? "true" : "false")
        << "\n";

    std::cout
        << "[STATE] Current state: "
        << fire.currentStateName()
        << "\n";

    stateResult = fire.advanceState();

    std::cout
        << "[STATE] advanceState() returned: "
        << (stateResult ? "true" : "false")
        << "\n";

    std::cout
        << "[STATE] Current state: "
        << fire.currentStateName()
        << "\n";

    /*
     * ==========================================================
     * 4. INVALID STATE TRANSITION
     * ==========================================================
     *
     * Resolved is terminal.
     *
     * This gives us the practical's required failure case.
     */

    std::cout << "\n--- Invalid State Transition Test ---\n";

    bool invalidState =
        fire.advanceState();

    std::cout
        << "[STATE] Attempted advance from Resolved.\n";

    std::cout
        << "[STATE] Succeeded? "
        << (invalidState ? "true" : "false")
        << "\n";

    /*
     * ==========================================================
     * 5. OBSERVER PATTERN
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 3: OBSERVER PATTERN\n";
    std::cout << "------------------------------------------------------------\n";

    TestIncidentObserver loggerObserver(
        "Incident Logger");

    TestIncidentObserver dashboardObserver(
        "Incident Dashboard");

    fire.attach(
        &loggerObserver);

    fire.attach(
        &dashboardObserver);

    std::cout
        << "[TEST] Two observers attached.\n";

    /*
     * Explicit notification test.
     *
     * Both observers should receive this.
     */

    fire.notify(
        "Emergency condition updated");

    /*
     * Test detach as well.
     */

    std::cout << "\n--- Detaching Dashboard Observer ---\n";

    fire.detach(
        &dashboardObserver);

    fire.notify(
        "Only logger should receive this update");

    /*
     * ==========================================================
     * 6. COMMAND + MEDIATOR
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 4: COMMAND + MEDIATOR\n";
    std::cout << "------------------------------------------------------------\n";

    std::cout
        << "\n--- Dispatch Security to Library ---\n";

    console.submit(
        new DispatchUnitCommand(
            &security,
            "Library",
            &fire));

    std::cout
        << "\n--- Dispatch Medical to Library ---\n";

    console.submit(
        new DispatchUnitCommand(
            &medical,
            "Library",
            &fire));

    /*
     * DispatchUnitCommand is a concrete Command.
     *
     * OperatorConsole = Invoker
     * ResponseUnit     = Receiver
     *
     * ResponseUnit also talks to IncidentCoordinator,
     * demonstrating Command + Mediator integration.
     */

    /*
     * ==========================================================
     * 7. LOCKDOWN COMMAND
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 5: LOCKDOWN COMMAND\n";
    std::cout << "------------------------------------------------------------\n";

    console.submit(
        new LockdownZoneCommand(
            &access,
            "Library"));

    /*
     * ==========================================================
     * 8. ADAPTER DIRECT TEST
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 6: ADAPTER PATTERN\n";
    std::cout << "------------------------------------------------------------\n";

    bool adapterResult =
        alerts.broadcastAlert(
            "FIRE: Evacuate Library immediately",
            "Library");

    std::cout
        << "[ADAPTER TEST] Result: "
        << (adapterResult
                ? "SUCCESS"
                : "FAILED")
        << "\n";

    /*
     * Expected flow:
     *
     * AlertService
     *      ->
     * INotificationChannel
     *      ->
     * LegacyGatewayAdapter
     *
     * Adapter:
     *
     * string zone
     *      ->
     * integer zone
     *
     * message
     *      ->
     * signal code
     *
     * std::string
     *      ->
     * const char*
     *
     * LegacyGatewayAdapter
     *      ->
     * LegacySecurityGateway::sendRawSignal()
     */

    /*
     * ==========================================================
     * 9. COMMAND + ADAPTER
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 7: COMMAND + ADAPTER\n";
    std::cout << "------------------------------------------------------------\n";

    console.submit(
        new IssueAlertCommand(
            &alerts,
            "Evacuate Library via East exit",
            "Library"));

    /*
     * This creates:
     *
     * OperatorConsole
     *      ->
     * IssueAlertCommand
     *      ->
     * AlertService
     *      ->
     * LegacyGatewayAdapter
     *      ->
     * LegacySecurityGateway
     */

    /*
     * ==========================================================
     * 10. COMMAND UNDO
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 8: COMMAND UNDO\n";
    std::cout << "------------------------------------------------------------\n";

    std::cout
        << "\n--- Cancel previous command ---\n";

    console.submit(
        new CancelActionCommand(
            &console));

    std::cout
        << "\n--- Cancel previous command again ---\n";

    console.submit(
        new CancelActionCommand(
            &console));

    /*
     * ==========================================================
     * 11. FACADE
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 9: FACADE PATTERN\n";
    std::cout << "------------------------------------------------------------\n";

    bool facadeResult =
        facade.initiateEvacuation(
            "Engineering Building",
            "Fire detected on second floor");

    std::cout
        << "[FACADE TEST] Result: "
        << (facadeResult
                ? "SUCCESS"
                : "FAILED")
        << "\n";

    /*
     * ==========================================================
     * 12. DIRECT SUBSYSTEM ACCESS
     * ==========================================================
     *
     * Important:
     *
     * Facade does not prevent clients from using the subsystems
     * directly.
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 10: DIRECT SUBSYSTEM ACCESS\n";
    std::cout << "------------------------------------------------------------\n";

    access.restrictZone(
        "Chemistry Lab");

    alerts.broadcastAlert(
        "Security notice for Chemistry Lab",
        "Chemistry Lab");

    /*
     * ==========================================================
     * 13. FAILURE CASE - ADAPTER / ALERT SERVICE
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 11: INVALID ALERT\n";
    std::cout << "------------------------------------------------------------\n";

    bool invalidAlert =
        alerts.broadcastAlert(
            "This should fail",
            "");

    std::cout
        << "[INVALID ALERT] Accepted? "
        << (invalidAlert
                ? "true"
                : "false")
        << "\n";

    /*
     * ==========================================================
     * 14. SECOND INCIDENT / DIFFERENT RUNTIME DATA
     * ==========================================================
     *
     * The practical requires at least two incidents or operational
     * contexts with different runtime data.
     */

    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "TEST 12: SECOND INCIDENT\n";
    std::cout << "------------------------------------------------------------\n";

    Incident chemicalLeak(
        "INC-002",
        "Chemical Leak",
        "Chemistry Laboratory",
        5);

    chemicalLeak.setState(
        new ReportedState());

    TestIncidentObserver secondObserver(
        "Second Incident Monitor");

    chemicalLeak.attach(
        &secondObserver);

    chemicalLeak.notify(
        "Chemical leak reported");

    std::cout
        << "[INC-002] Current state: "
        << chemicalLeak.currentStateName()
        << "\n";

    chemicalLeak.advanceState();

    std::cout
        << "[INC-002] Current state after advance: "
        << chemicalLeak.currentStateName()
        << "\n";

    /*
     * ==========================================================
     * END
     * ==========================================================
     */

    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "                ALL TESTS COMPLETED\n";
    std::cout << "============================================================\n";

    return 0;
}