#include "DispatchUnitCommand.h"
#include "ResponseUnit.h"
#include "incident/Incident.h"
#include <iostream>

DispatchUnitCommand::DispatchUnitCommand(ResponseUnit *unit, const std::string &location, Incident *incident) : unit(unit), location(location), incident(incident)
{
}

void DispatchUnitCommand::execute()
{
    if (!unit)
    {
        std::cout << "[DispatchUnitCommand] no receiver\n";
        return;
    }

    std::cout << "[DispatchUnitCommand] executing: " << describe() << std::endl;
    unit->dispatch(location);
    executed = true;

    if (incident && incident->currentStateName() == "Reported")
    {
        incident->advanceState(); // Reported -> Dispatched
    }
}

void DispatchUnitCommand::undo()
{
    if (!executed)
    {
        std::cout << "[Command] undo skipped: never executed.\n";
        return;
    }
    if (!unit)
        return;
    std::cout << "[Command] undo: recall " << unit->getName() << "\n";
    unit->recall();
    executed = false;
}

std::string DispatchUnitCommand::describe() const
{
    return "DispatchUnit(" + (unit ? unit->getName() : "null") + " -> " + location + ")";
}