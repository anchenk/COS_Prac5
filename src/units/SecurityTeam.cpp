#include "SecurityTeam.h"
#include <iostream>

SecurityTeam::SecurityTeam(const std::string &name, IIncidentMediator *mediator)
    : ResponseUnit(name, mediator) {}

void SecurityTeam::dispatch(const std::string &location)
{
    if (deployed)
    {
        std::cout << "[SecurityTeam " << getName()
                  << "] already deployed at " << location
                  << "; ignoring duplicate dispatch.\n";
        return;
    }
    deployed = true;
    this->location = location;
    std::cout << "[SecurityTeam " << getName() << "] deployed to "
              << location << "\n";
    reportStatusChange("security dispatched to " + location);
}

void SecurityTeam::recall()
{
    if (!deployed)
    {
        std::cout << "[SecurityTeam " << getName()
                  << "] recall ignored: not deployed.\n";
        return;
    }
    std::cout << "[SecurityTeam " << getName() << "] recalled from "
              << location << "\n";
    deployed = false;
    location.clear();
    reportStatusChange("security recalled");
}

std::string SecurityTeam::getStatus() const
{
    return deployed ? "Deployed" : "Standby";
}