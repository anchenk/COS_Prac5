#include "../../include/incident/IncidentCoordinator.h"
#include "../../include/units/ResponseUnit.h"
#include <iostream>
#include <algorithm>

IncidentCoordinator::IncidentCoordinator() {}
IncidentCoordinator::~IncidentCoordinator() {}

void IncidentCoordinator::registerUnit(ResponseUnit* unit) {
    units_.push_back(unit);
}

void IncidentCoordinator::notifyUnitStatusChanged(ResponseUnit* unit, const std::string& event) {
    std::cout << "[Mediator] " << unit->getName() << " reported: " << event << "\n";

    // Meaningful coordination: when a security team arrives on scene,
    // tell every OTHER registered unit so they can react - this is the
    // required "one colleague's change causes the mediator to coordinate
    // behaviour involving other colleagues."
    if (event == "arrived") {
        for (std::vector<ResponseUnit*>::iterator it = units_.begin();
             it != units_.end(); ++it) {
            if (*it != unit) {
                std::cout << "[Mediator] Notifying " << (*it)->getName()
                          << " that " << unit->getName() << " has arrived.\n";
                // Real coordination hook - e.g. a FacilitiesCrew could
                // unlock a door once Security has arrived. The exact
                // reaction depends on Anchen's concrete unit types,
                // but the mediator's job (deciding WHO reacts and WHEN)
                // is fully implemented here.
            }
        }
    }
}