#ifndef CAMPUSGUARD_COMMAND_H
#define CAMPUSGUARD_COMMAND_H

#include <string>

// TODO(Ancheen): Command pattern base.
// Concrete commands (create in the same directory), each with a real
// receiver and real domain behaviour (not just printing their name):
//   DispatchUnitCommand   -> receiver: ResponseUnit
//   LockdownZoneCommand   -> receiver: AccessControlSystem (Katlego's)
//   IssueAlertCommand     -> receiver: AlertService (Katlego's)
//   CancelActionCommand   -> undoes the last executed command
//
// execute() must trigger real behaviour; undo() should be meaningful
// (e.g. recall a dispatched unit) for at least CancelActionCommand's target.
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string describe() const = 0;
};

#endif // CAMPUSGUARD_COMMAND_H
