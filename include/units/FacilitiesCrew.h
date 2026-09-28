#ifndef CAMPUSGUARD_FACILITIESCREW_H
#define CAMPUSGUARD_FACILITIESCREW_H

#include "ResponseUnit.h"

class FacilitiesCrew : public ResponseUnit
{
public:
    FacilitiesCrew(const std::string &name, IIncidentMediator *mediator);

    void dispatch(const std::string &location) override;
    void recall() override;
    std::string getStatus() const override;

private:
    bool deployed = false;
    std::string location;
};

#endif