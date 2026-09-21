#ifndef CAMPUSGUARD_INCIDENTCOORDINATOR_H
#define CAMPUSGUARD_INCIDENTCOORDINATOR_H

#include <string>
#include <vector>

class ResponseUnit; // forward declaration, defined in units/ResponseUnit.h
class Incident;

// Mediator participant (abstract mediator interface).
// Colleagues (ResponseUnit subclasses, access-control systems, etc.)
// call back into the mediator instead of knowing about each other directly.
class IIncidentMediator {
public:
    virtual ~IIncidentMediator() {}
    virtual void notifyUnitStatusChanged(ResponseUnit* unit, const std::string& event) = 0;
};

// TODO(Musa): Concrete mediator.
// Register colleagues (ResponseUnit instances) here. When one colleague's
// notifyUnitStatusChanged fires, decide what the OTHER colleagues should
// do as a result - that reaction is the required visible behaviour:
// "at least one meaningful change in one colleague must result in the
// mediator coordinating behaviour involving other colleagues."
class IncidentCoordinator : public IIncidentMediator {
public:
    IncidentCoordinator();
    virtual ~IncidentCoordinator();

    void registerUnit(ResponseUnit* unit);
    void notifyUnitStatusChanged(ResponseUnit* unit, const std::string& event) override;

private:
    std::vector<ResponseUnit*> units_; // not owned
};

#endif // CAMPUSGUARD_INCIDENTCOORDINATOR_H
