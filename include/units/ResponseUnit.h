#ifndef CAMPUSGUARD_RESPONSEUNIT_H
#define CAMPUSGUARD_RESPONSEUNIT_H

#include <string>

class IIncidentMediator; // forward declaration

// TODO(Ancheen): ResponseUnit is:
//   - the Receiver for Command pattern (DispatchUnitCommand etc. call
//     into concrete units' dispatch()/recall() methods)
//   - a Colleague in the Mediator pattern (holds a reference to the
//     mediator, calls back into it when its own status changes)
//
// Concrete subclasses (create alongside this file):
//   SecurityTeam, MedicalResponder, FacilitiesCrew
class ResponseUnit {
public:
    ResponseUnit(const std::string& name, IIncidentMediator* mediator);
    virtual ~ResponseUnit();

    virtual void dispatch(const std::string& location) = 0;
    virtual void recall() = 0;
    virtual std::string getStatus() const = 0;

    std::string getName() const;

protected:
    // Colleagues call this on the mediator when their own state changes,
    // e.g. after dispatch() completes.
    void reportStatusChange(const std::string& event);

private:
    std::string name_;
    IIncidentMediator* mediator_; // not owned
};

#endif // CAMPUSGUARD_RESPONSEUNIT_H
