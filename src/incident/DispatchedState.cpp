#include "../../include/incident/DispatchedState.h"
#include "../../include/incident/ContainedState.h"
#include "../../include/incident/Incident.h"
#include <iostream>

bool DispatchedState::advance(Incident& incident) {
    incident.setState(new ContainedState());
    return true;
}

std::string DispatchedState::name() const {
    return "Dispatched";
}