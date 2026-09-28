#ifndef CAMPUSGUARD_CONTAINEDSTATE_H
#define CAMPUSGUARD_CONTAINEDSTATE_H

#include "IncidentState.h"

class ContainedState : public IncidentState {
public:
    bool advance(Incident& incident) override;
    std::string name() const override;
};

#endif