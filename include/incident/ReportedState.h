#ifndef CAMPUSGUARD_REPORTEDSTATE_H
#define CAMPUSGUARD_REPORTEDSTATE_H

#include "IncidentState.h"

class ReportedState : public IncidentState {
public:
    bool advance(Incident& incident) override;
    std::string name() const override;
};

#endif