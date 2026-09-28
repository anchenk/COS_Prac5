#include "../../include/incident/ResolvedState.h"
#include "../../include/incident/Incident.h"
#include <iostream>

bool ResolvedState::advance(Incident& incident) {
    // Resolved is terminal - there's nowhere left to advance to.
    // This is the illegal-transition case: rejected, not silently ignored.
    std::cerr << "Cannot advance: incident is already Resolved (terminal state).\n";
    return false;
}

std::string ResolvedState::name() const {
    return "Resolved";
}