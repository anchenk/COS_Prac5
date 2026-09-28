#ifndef CAMPUSGUARD_INCIDENT_H
#define CAMOUSGUARD_INCIDENT_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "IIncidentObserver.h"

// SUbject participant in the Observer pattern
// Domain entity (id, location, status)

class Incident
{
public:
    enum class Status
    {
        Reported,
        Acknowledged,
        Responding,
        Resolved
    };

    Incident(const std::string &id,
             const std::string &location,
             const std::string &description)
        : id(id),
          location(location),
          description(description),
          status(Status::Reported) {}

    // observer subscribed per instance
    Incident(const Incident &) = delete;
    Incident &operator=(const Incident &) = delete;

    // observer management
    void attach(IIncidentObserver *obs)
    {
        if (obs)
        {
            observers.push_back(obs);
            std::cout << "[Incident " << id << "] observer attached ("
                      << observers.size() << " total)\n";
        }
    }

    void detach(IIncidentObserver *obs)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), obs),
                        observers.end());
    }

    // state changes

    void setStatus(Status s, const std::string &reason)
    {
        status = s;
        notify(reason);
    }

    // accessors
    const std::string &getId() const { return id; }
    const std::string &getLocation() const { return location; }
    const std::string &getDescription() const { return description; }
    Status getStatus() const { return status; }

    std::string statusToString() const
    {
        switch (status)
        {
        case Status::Reported:
            return "Reported";
        case Status::Acknowledged:
            return "Acknowledged";
        case Status::Responding:
            return "Responding";
        case Status::Resolved:
            return "Resolved";
        }
        return "Unknown";
    }

private:
    void notify(const std::string &reason)
    {
        for (auto *o : observers)
        {
            if (o)
                o->onIncidentChanged(*this, reason);
        }
    }
    std::string id;
    std::string location;
    std::string description;
    Status status;
    std::vector<IIncidentObserver *> observers;
};

#endif