#ifndef CAMPUSGUARD_INCIDENTSTATE_H
#define CAMPUSGUARD_INCIDENTSTATE_H

#include <string>

class Incident; // forward declaration

// TODO(Musa): State pattern base.
// Concrete states (create in the same directory):
//   ReportedState, DispatchedState, ContainedState, ResolvedState
// Each concrete state decides which transitions are legal from itself.
// Illegal transitions should be rejected (this is your required
// failure/invalid-operation case) rather than silently ignored -
// e.g. throw std::logic_error or return false with a logged reason.
class IncidentState {
public:
    virtual ~IncidentState() {}

    // Called by Incident when the operator/mediator requests a transition.
    // Implementations decide whether the requested next state is legal
    // from the current one, and perform it via incident.setState(...).
    virtual bool advance(Incident& incident) = 0;

    virtual std::string name() const = 0;
};

#endif // CAMPUSGUARD_INCIDENTSTATE_H
