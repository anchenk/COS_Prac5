#include "../../include/incident/IncidentCoordinator.h"
#include "../../include/units/ResponseUnit.h"

// TODO(Musa): implement registerUnit and the coordination logic in
// notifyUnitStatusChanged - this is where "one colleague's change
// causes the mediator to coordinate the others" becomes visible.
IncidentCoordinator::IncidentCoordinator() {}
IncidentCoordinator::~IncidentCoordinator() {}

void IncidentCoordinator::registerUnit(ResponseUnit* unit) {
    units_.push_back(unit);
}

void IncidentCoordinator::notifyUnitStatusChanged(ResponseUnit* unit, const std::string& event) {
    // TODO: react - e.g. if a SecurityTeam reports "arrived", tell
    // FacilitiesCrew to unlock a specific door for them.
}
