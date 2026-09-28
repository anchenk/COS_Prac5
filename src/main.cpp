#include <iostream>
#include <iostream>
#include <string>

#include "../include/incident/IncidentCoordinator.h"
#include "../include/commands/OperatorConsole.h"

#include "../include/facade/AccessControlSystem.h"
#include "../include/facade/AlertService.h"
#include "../include/facade/EmergencyOperationsFacade.h"

#include "../include/adapter/LegacyGatewayAdapter.h"

int main()
{
    std::cout << "==========================================" << std::endl;
    std::cout << "          CAMPUSGUARD SYSTEM" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << std::endl;

    /*
     * ==========================================================
     * SHARED CAMPUSGUARD COMPONENTS
     * ==========================================================
     */

    // Mediator
    IncidentCoordinator coordinator;

    // Command invoker
    OperatorConsole console;

    // Access-control subsystem
    AccessControlSystem access;

    /*
     * ==========================================================
     * ADAPTER PATTERN
     * ==========================================================
     *
     * IMPORTANT:
     *
     * We do NOT create LegacySecurityGateway directly here.
     *
     * LegacyGatewayAdapter already contains:
     *
     *      LegacySecurityGateway gateway_;
     *
     * internally.
     *
     * Therefore the adapter owns and communicates with the
     * legacy system.
     */

    LegacyGatewayAdapter adapter;

    /*
     * AlertService expects an INotificationChannel*.
     *
     * LegacyGatewayAdapter inherits from INotificationChannel,
     * therefore its address can be passed here.
     */
    AlertService alerts(&adapter);

    /*
     * ==========================================================
     * FACADE PATTERN
     * ==========================================================
     *
     * The facade receives the existing subsystem objects.
     *
     * It does NOT own them.
     */
    EmergencyOperationsFacade facade(
        &access,
        &alerts,
        &coordinator);

    std::cout << std::endl;

    /*
     * ==========================================================
     * SCENARIO 1
     * FIRE IN ENGINEERING BUILDING
     * ==========================================================
     */

    std::cout << "==========================================" << std::endl;
    std::cout << "SCENARIO 1: ENGINEERING BUILDING FIRE" << std::endl;
    std::cout << "==========================================" << std::endl;

    std::string engineeringZone = "ENGINEERING_BLOCK_A";

    std::string fireMessage =
        "FIRE detected in Engineering Block A. "
        "Proceed to the nearest emergency exit.";

    std::cout
        << "[Operator] Fire emergency reported in "
        << engineeringZone
        << std::endl;

    std::cout
        << "[Operator] Starting emergency evacuation..."
        << std::endl;

    bool scenario1Result =
        facade.initiateEvacuation(
            engineeringZone,
            fireMessage);

    if (scenario1Result)
    {
        std::cout
            << "[MAIN] Scenario 1 evacuation successfully initiated."
            << std::endl;
    }
    else
    {
        std::cout
            << "[MAIN] Scenario 1 evacuation FAILED."
            << std::endl;
    }

    std::cout << std::endl;

    /*
     * ==========================================================
     * DEMONSTRATE INDEPENDENT SUBSYSTEM USE
     * ==========================================================
     *
     * The Facade must NOT make the underlying systems inaccessible.
     *
     * We can still interact with AccessControlSystem directly.
     */

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "DIRECT ACCESS CONTROL OPERATION" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    bool labRestricted =
        access.restrictZone("CHEMISTRY_LAB");

    if (labRestricted)
    {
        std::cout
            << "[MAIN] Chemistry Lab successfully restricted."
            << std::endl;
    }
    else
    {
        std::cout
            << "[MAIN] Could not restrict Chemistry Lab."
            << std::endl;
    }

    std::cout << std::endl;

    /*
     * ==========================================================
     * DIRECT ALERT
     * ==========================================================
     *
     * This demonstrates:
     *
     * Main
     *   -> AlertService
     *   -> INotificationChannel
     *   -> LegacyGatewayAdapter
     *   -> LegacySecurityGateway
     */

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "DIRECT SECURITY ALERT" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    bool securityAlert =
        alerts.broadcastAlert(
            "Security personnel report to Engineering Block A.",
            engineeringZone);

    if (securityAlert)
    {
        std::cout
            << "[MAIN] Security alert sent successfully."
            << std::endl;
    }
    else
    {
        std::cout
            << "[MAIN] Security alert failed."
            << std::endl;
    }

    std::cout << std::endl;

    /*
     * ==========================================================
     * SCENARIO 2
     * SECURITY INCIDENT AT MAIN LIBRARY
     * ==========================================================
     */

    std::cout << "==========================================" << std::endl;
    std::cout << "SCENARIO 2: MAIN LIBRARY INCIDENT" << std::endl;
    std::cout << "==========================================" << std::endl;

    std::string libraryZone = "MAIN_LIBRARY";

    std::string libraryMessage =
        "Security emergency reported in the Main Library. "
        "Evacuate the building immediately.";

    std::cout
        << "[Operator] Security incident reported in "
        << libraryZone
        << std::endl;

    bool scenario2Result =
        facade.initiateEvacuation(
            libraryZone,
            libraryMessage);

    if (scenario2Result)
    {
        std::cout
            << "[MAIN] Scenario 2 evacuation successfully initiated."
            << std::endl;
    }
    else
    {
        std::cout
            << "[MAIN] Scenario 2 evacuation FAILED."
            << std::endl;
    }

    std::cout << std::endl;

    /*
     * ==========================================================
     * INVALID OPERATION TEST
     * ==========================================================
     *
     * The practical requires at least one invalid operation or
     * failure case to be handled sensibly.
     *
     * Your AlertService already checks for an empty zone.
     */

    std::cout << "==========================================" << std::endl;
    std::cout << "FAILURE TEST: EMPTY ZONE" << std::endl;
    std::cout << "==========================================" << std::endl;

    bool invalidAlert =
        alerts.broadcastAlert(
            "This alert should fail.",
            "");

    if (!invalidAlert)
    {
        std::cout
            << "[MAIN] Invalid operation correctly rejected."
            << std::endl;
    }
    else
    {
        std::cout
            << "[MAIN] WARNING: Invalid operation was accepted."
            << std::endl;
    }

    std::cout << std::endl;

    /*
     * ==========================================================
     * RESTORE AN AREA
     * ==========================================================
     */

    std::cout << "==========================================" << std::endl;
    std::cout << "RESTORING NORMAL ACCESS" << std::endl;
    std::cout << "==========================================" << std::endl;

    bool restored =
        access.unlockZone("CHEMISTRY_LAB");

    if (restored)
    {
        std::cout
            << "[MAIN] Chemistry Lab returned to normal access."
            << std::endl;
    }
    else
    {
        std::cout
            << "[MAIN] Failed to restore Chemistry Lab."
            << std::endl;
    }

    std::cout << std::endl;

    std::cout << "==========================================" << std::endl;
    std::cout << "        CAMPUSGUARD RUN COMPLETE" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
