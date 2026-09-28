#include "LockdownZoneCommand.h"
#include "AccessControlSystem.h"
#include <iostream>

LockdownZoneCommand::LockdownZoneCommand(AccessControlSystem *acs,
                                         const std::string &zone)
    : acs(acs), zone(zone) {}

void LockdownZoneCommand::execute()
{
    if (!acs)
    {
        std::cout << "[Lockdown] no receiver.\n";
        return;
    }
    std::cout << "[Command] execute: " << describe() << "\n";
    previousState = acs->isLocked(zone);
    acs->lockZone(zone);
    executed = true;
}

void LockdownZoneCommand::undo()
{
    if (!executed || !acs)
        return;
    std::cout << "[Command] undo: " << describe() << "\n";

    if (previousState)
        acs->lockZone(zone);
    else
        acs->unlockZone(zone);
    executed = false;
}

std::string LockdownZoneCommand::describe() const
{
    return "LockdownZone(" + zone + ")";
}