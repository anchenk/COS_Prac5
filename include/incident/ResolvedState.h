#ifndef CAMPUSGUARD_RESOLVEDSTATE_H
#define CAMPUSGUARD_RESOLVEDSTATE_H

#include "IncidentState.h"

class ResolvedState : public IncidentState {
public:
    bool advance(Incident& incident) override;
    std::string name() const override;
};

#endif