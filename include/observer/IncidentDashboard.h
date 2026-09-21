#ifndef CAMPUSGUARD_INCIDENTDASHBOARD_H
#define CAMPUSGUARD_INCIDENTDASHBOARD_H

#include "IIncidentObserver.h"
#include "Incident.h"
#include <iostream>
#include <map>

// concrete observer
//  "live dashboard" with latest reason per incident
//  multiple differently behaving observers can exist

class IncidentDashboard : public IIncidentObserver
{
public:
    void onIncidentChanged(const Incident &incident,
                           const std::string &reason) override
    {
        lastReason[incident.getId()] = reason;
        std::cout << "Dashboard: " << incident.getId()
                  << " = " << incident.statusToString() << "\n";
    }

    std::string lastReasonFor(const std::string &id) const
    {
        auto it = lastReason.find(id);
        return it == lastReason.end() ? "(none)" : it->second;
    }

private:
    std::map<std::string, std::string> lastReason;
};

#endif