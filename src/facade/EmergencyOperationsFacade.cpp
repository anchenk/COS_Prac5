#include "../../include/facade/EmergencyOperationsFacade.h"

// TODO(Katlego): implement initiateEvacuation to call >= 3 subsystem
// operations in sequence (e.g. access_->lockZone, alerts_->broadcastAlert,
// coordinator interaction).
EmergencyOperationsFacade::EmergencyOperationsFacade(AccessControlSystem *access,
                                                     AlertService *alerts,
                                                     IncidentCoordinator *coordinator)
    : access_(access), alerts_(alerts), coordinator_(coordinator) {}

EmergencyOperationsFacade::~EmergencyOperationsFacade() {}

bool EmergencyOperationsFacade::initiateEvacuation(const std::string &zoneId, const std::string &message)
{
    if (zoneId.empty())
    {
        std::cout << "[EmergencyOperationsFacade] ERROR: Zone ID cannot be empty." << std::endl;
        return false;
    }
    if (message.empty())
    {
        std::cout << "[EmergencyOperationsFacade] ERROR: Message cannot be empty." << std::endl;
        return false;
    }

    if (access_ == nullptr)
    {
        std::cout << "[EmergencyOperationsFacade] ERROR: AccessControlSystem is not set." << std::endl;
        return false;
    }

    if (alerts_ == nullptr)
    {
        std::cout << "[EmergencyOperationsFacade] ERROR: AlertService is not set." << std::endl;
        return false;
    }

    bool restrict = access_->restrictZone(zoneId);

    if (!restrict)
    {
        std::cout << "[EmergencyOperationsFacade] ERROR: Failed to restrict zone " << zoneId << std::endl;
        return false;
    }

    std::string emergencyExitZone = zoneId + "::EMERGENCY_EXIT";

    bool exitsOpened = access_->unlockZone(emergencyExitZone);

    if (!exitsOpened)
    {
        std::cout << "[EmergencyOperationsFacade] ERROR: Failed to unlock emergency exits for zone " << zoneId << std::endl;
        return false;
    }

    std::string evacuationMessage = "EVACUATE: " + message;

    bool alertSent = alerts_->broadcastAlert(evacuationMessage, zoneId);

    if (!alertSent)
    {
        std::cout << "[EmergencyOperationsFacade] ERROR: Failed to send evacuation alert for zone " << zoneId << std::endl;
        return false;
    }

    std::cout << "[FACADE] Evacuation initiated for zone " << zoneId << std::endl;

    return true;
}
