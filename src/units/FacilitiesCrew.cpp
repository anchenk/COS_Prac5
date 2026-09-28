#include "FacilitiesCrew.h"
#include <iostream>

FacilitiesCrew::FacilitiesCrew(const std::string &name,
                               IIncidentMediator *mediator)
    : ResponseUnit(name, mediator) {}

void FacilitiesCrew::dispatch(const std::string &location)
{
    if (deployed)
    {
        std::cout << "[FacilitiesCrew " << getName()
                  << "] already working at " << location << "\n";
        return;
    }
    deployed = true;
    this->location = location;
    std::cout << "[FacilitiesCrew " << getName() << "] dispatched to "
              << location << "\n";
    reportStatusChange("facilities dispatched to " + location);
}

void FacilitiesCrew::recall()
{
    if (!deployed)
    {
        std::cout << "[FacilitiesCrew " << getName()
                  << "] recall ignored: not deployed.\n";
        return;
    }
    std::cout << "[FacilitiesCrew " << getName() << "] returned from "
              << location << "\n";
    deployed = false;
    location.clear();
    reportStatusChange("facilities recalled");
}

std::string FacilitiesCrew::getStatus() const
{
    return deployed ? "Working" : "Standby";
}