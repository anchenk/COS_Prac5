#include "../../include/units/ResponseUnit.h"
#include "../../include/incident/IncidentCoordinator.h"

// TODO(Anchen): base class plumbing; concrete subclasses
// (SecurityTeam.cpp etc.) go in this same directory.
ResponseUnit::ResponseUnit(const std::string &name, IIncidentMediator *mediator)
    : name(name), mediator(mediator) {}

ResponseUnit::~ResponseUnit() {}

std::string ResponseUnit::getName() const { return name; }

void ResponseUnit::reportStatusChange(const std::string &event)
{
    if (mediator)
    {
        mediator->notifyUnitStatusChanged(this, event);
    }
}
