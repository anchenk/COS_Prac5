#ifndef CAMPUSGUARD_INCIDENTLOGGER_H
#define CAMPUSGUARD_INCIDENTLOGGER_H

#include "IIncidentObserver.h"
#include "Incident.h"
#include <iostream>

// concrete observer: writes on every incident change to this console log

class IncidentLogger : public IIncidentObserver
{
public:
    void onIncidentChanged(const Incident &incident,
                           const std::string &reason) override
    {
        std::cout << "Incident " << incident.getId()
                  << " (" << incident.getLocation() << ")"
                  << " -> " << incident.statusToString()
                  << " | reason: " << reason << "\n";
    }
};

#endif