#include "../../include/incident/ContainedState.h"
#include "../../include/incident/ResolvedState.h"
#include "../../include/incident/Incident.h"
#include <iostream>

bool ContainedState::advance(Incident& incident) {
    incident.setState(new ResolvedState());
    return true;
}

std::string ContainedState::name() const {
    return "Contained";
}