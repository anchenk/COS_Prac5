#include "MedicalResponder.h"
#include <iostream>

MedicalResponder::MedicalResponder(const std::string &name,
                                   IIncidentMediator *mediator)
    : ResponseUnit(name, mediator) {}

void MedicalResponder::dispatch(const std::string &location)
{
    if (deployed)
    {
        std::cout << "[MedicalResponder " << getName()
                  << "] already on-scene at " << location << "\n";
        return;
    }
    deployed = true;
    this->location = location;
    std::cout << "[MedicalResponder " << getName() << "] dispatched to "
              << location << "\n";
    reportStatusChange("medical dispatched to " + location);
}

void MedicalResponder::recall()
{
    if (!deployed)
    {
        std::cout << "[MedicalResponder " << getName()
                  << "] recall ignored: not deployed.\n";
        return;
    }
    std::cout << "[MedicalResponder " << getName() << "] returned to base from "
              << location << "\n";
    deployed = false;
    location.clear();
    reportStatusChange("medical recalled");
}

std::string MedicalResponder::getStatus() const
{
    return deployed ? "OnScene" : "Standby";
}