#ifndef CAMPUSGUARD_INCIDENT_H
#define CAMPUSGUARD_INCIDENT_H

#include <string>
#include <vector>
#include "IncidentState.h"
#include "../observer/IIncidentObserver.h"

// TODO(Musa): Incident is:
//   - the Context in the State pattern (holds an IncidentState*)
//   - the Subject in the Observer pattern (holds IIncidentObserver* list)
//   - a Colleague in the Mediator pattern (registers with IncidentCoordinator)
//
// Ownership: decide who owns the IncidentState* (Incident should own and
// delete its current state on destruction/transition - document this
// decision in your PDF's ownership section).
class Incident {
public:
    Incident(const std::string& id, const std::string& type,
              const std::string& location, int severity);
    virtual ~Incident();

    // State pattern: delegate to current state, which decides legality.
    bool advanceState();
    void setState(IncidentState* newState); // called by concrete states
    std::string currentStateName() const;

    // Observer pattern
    void attach(IIncidentObserver* observer);
    void detach(IIncidentObserver* observer);
    void notify(const std::string& reason);

    std::string getId() const;
    std::string getType() const;
    std::string getLocation() const;
    int getSeverity() const;

private:
    std::string id_;
    std::string type_;
    std::string location_;
    int severity_;
    IncidentState* state_; // owned
    std::vector<IIncidentObserver*> observers_; // not owned
};

#endif // CAMPUSGUARD_INCIDENT_H
