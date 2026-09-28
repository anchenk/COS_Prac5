#ifndef CAMPUSGUARD_DISPATCHEDSTATE_H
#define CAMPUSGUARD_DISPATCHEDSTATE_H

#include "IncidentState.h"

class DispatchedState : public IncidentState {
public:
    bool advance(Incident& incident) override;
    std::string name() const override;
};

#endif