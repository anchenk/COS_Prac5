#ifndef CAMPUSGUARD_DISPATCHUNITCOMMAND_H
#define CAMPUSGUARD_DISPATCHUNITCOMMAND_H

#include "Command.h"
#include <string>

class ResponseUnit;
class Incident;

// concrete command to dispatch a unit to a location
// reciever is responseunit which nudges the incident into responding

class DispatchUnitCommand : public Command
{
public:
    DispatchUnitCommand(ResponseUnit *unit, const std::string &location, Incident *incident = nullptr);
    void execute() override;
    void undo() override;
    std::string describe() const override;

private:
    ResponseUnit *unit;
    std::string location;
    Incident *incident;
    bool executed = false;
};

#endif