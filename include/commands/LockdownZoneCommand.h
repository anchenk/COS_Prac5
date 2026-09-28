#ifndef CAMPUSGUARD_LOCKDOWNZONECOMMAND_H
#define CAMPUSGUARD_LOCKDOWNZONECOMMAND_H

#include "Command.h"
#include <string>

class AccessControlSystem;

// Concrete Command: lock a zone via AccessControlSystem.
// Receiver: AccessControlSystem.

class LockdownZoneCommand : public Command {
public:
    LockdownZoneCommand(AccessControlSystem* acs, const std::string& zone);

    void execute() override;
    void undo()    override;
    std::string describe() const override;

private:
    AccessControlSystem* acs;
    std::string zone;
    bool executed = false;
    bool lastExecuteSucceeded = false;
};

#endif