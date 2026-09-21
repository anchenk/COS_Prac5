#ifndef CAMPUSGUARD_IINCIDENTOBSERVER_H
#define CAMPUSGUARD_IINCIDENTOBSERVER_H

#include <string>

// Observer participant: anything that needs to react when an
// Incident's condition changes (e.g. a logger, a dashboard,
// a notification subscriber) implements this interface.
class Incident; // forward declaration, defined in incident/Incident.h

class IIncidentObserver {
public:
    virtual ~IIncidentObserver() {}

    // Called by Incident (the Subject) whenever its state changes.
    virtual void onIncidentChanged(const Incident& incident, const std::string& reason) = 0;
};

#endif // CAMPUSGUARD_IINCIDENTOBSERVER_H
