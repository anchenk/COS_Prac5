#ifndef CAMPUSGUARD_SECURITYTEAM_H
#define CAMPUSGUARD_SECURITYTEAM_H

#include "ResponseUnit.h"

class SecurityTeam : public ResponseUnit
{
public:
    SecurityTeam(const std::string &name, IIncidentMediator *mediator);

    void dispatch(const std::string &location) override;
    void recall() override;
    std::string getStatus() const override;

private:
    bool deployed = false;
    std::string location;
};

#endif