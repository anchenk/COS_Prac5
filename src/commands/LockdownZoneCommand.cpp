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
        std::cout << "[LockdownZoneCommand] no receiver; aborting.\n";
        return;
    }
    std::cout << "[Command] execute: " << describe() << "\n";
    lastExecuteSucceeded = acs->lockZone(zone);
    executed = true;

    if (!lastExecuteSucceeded)
    {
        std::cout << "[LockdownZoneCommand] lockZone failed for zone '"
                  << zone << "'. Invalid or unknown zone.\n";
    }
}

void LockdownZoneCommand::undo()
{
    if (!executed || !acs)
        return;

    if (!lastExecuteSucceeded)
    {
        std::cout << "[Command] undo skipped: execute() had no effect.\n";
        executed = false;
        return;
    }

    std::cout << "[Command] undo: " << describe() << "\n";
    bool ok = acs->unlockZone(zone);
    if (!ok)
    {
        std::cout << "[LockdownZoneCommand] undo: unlockZone failed for '"
                  << zone << "'.\n";
    }
    executed = false;
}

std::string LockdownZoneCommand::describe() const
{
    return "LockdownZone(" + zone + ")";
}