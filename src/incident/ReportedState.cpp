#include "../../include/incident/ReportedState.h"
#include "../../include/incident/DispatchedState.h"
#include "../../include/incident/Incident.h"
#include <iostream>

bool ReportedState::advance(Incident& incident) {
    incident.setState(new DispatchedState());
    return true;
}

std::string ReportedState::name() const {
    return "Reported";
}